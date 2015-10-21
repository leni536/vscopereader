#include<boost/program_options.hpp>
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>

using namespace std;
namespace po = boost::program_options;

class measurement
{
    private:
    vector<double> origin;
    double dt;
    vector<vector<double> > data;
    string buttons;

    measurement();
    public:
    measurement(istream& ves,istream& vsw);
    void writedata(ostream& out);
    friend ostream& operator<<(ostream& out,const measurement& meas);
};

measurement::measurement(istream& ves,istream& vsw) : origin(3)
{
    string line;

    do
    {
        if (ves.eof()) throw runtime_error("VES parse error");
        if (!getline(ves,line)) throw runtime_error("VES parse error");
    } while (line != "\"[Units]\"\r");
    if (!getline(ves,line)) throw runtime_error("VES parse error");
    if (!(ves >> dt)) throw runtime_error("VES parse error");

    do
    {
        if (ves.eof()) throw runtime_error("VES parse error");
        if (!getline(ves,line)) throw runtime_error("VES parse error");
    } while (line != "\"[Origin]\"\r");
    if (!(ves >> origin[0])) throw runtime_error("VES parse error");
    if (!(ves >> origin[1])) throw runtime_error("VES parse error");
    if (!(ves >> origin[2])) throw runtime_error("VES parse error");

    for(int i=0;i<5;i++) 
    {
        if (!getline(vsw,line)) throw runtime_error("VSW parse error");
    }
    istringstream ss(line);
    for(int i=0;i<2;i++)
    {
        if (!getline(ss,buttons,',')) throw runtime_error("VSW parse error");
    }
    if (buttons.size()<2) throw runtime_error("VSW parse error");
    buttons=buttons.substr(1,buttons.size()-3).c_str();
    
    for(int i=0;i<4;i++)
    {
        if (!getline(vsw,line)) throw runtime_error("VSW parse error");
    }
    while (vsw)
    {
        istream& is=getline(vsw,line);
        if (is.fail() || is.bad()) break;

        data.push_back(vector<double>(3*buttons.size()+1));
        istringstream ss2(line);

        for(int i=0;i<3*buttons.size()+1;i++)
        {
            string token;
            if(!getline(ss2,token,',')) throw runtime_error("VSW parse error");
            try
            {
                double value = stof(token);
                data.back()[i]=value;
            }
            catch (logic_error& err)
            {
                throw runtime_error("VSW parse error");
            }
        }

        data.back()[0]=data.back()[0]*dt;
        for(int i=0; i<buttons.size(); i++)
        {
            data.back()[3*i+1]=data.back()[3*i+1]/10000.-3.;
            data.back()[3*i+2]=data.back()[3*i+2]/10000.-3.;
            data.back()[3*i+3]=data.back()[3*i+3]/10000.;
        }
    }
}

ostream& operator<<(ostream& out,const measurement& meas)
{
    out << "Origin: " 
        << meas.origin[0] << ", " 
        << meas.origin[1] << ", " 
        << meas.origin[2]
    << endl;
    out << "Sampling interval: " << meas.dt << endl;
    out << "Buttons: " << meas.buttons << endl;
    return out;
}

void measurement::writedata(ostream& out)
{
    for(int i=0;i<data.size();i++)
    {
        for(int j=0;j<data[0].size();j++)
        {
            out << data[i][j] ;
            if (j<data[0].size()-1)
                out << ", ";
        }
        out << endl;
    }
}

int main(int argc, char* argv[])
{
    po::options_description desc("Usage");
    desc.add_options()
        ("help", "produce help message")
	("basename", po::value<string>(),"basename of the VES and VSW files")
	("output,o",po::value<string>()->default_value("-"),"output file name")
    ;
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);    
    
    if (vm.count("help")||!vm.count("basename")) {
        cout << desc << "\n";
        return 0;
    }
    string basename = vm["basename"].as<string>();
    string output   = vm["output"].as<string>();

    ifstream vesfile((basename+".VES").c_str());
    if (vesfile.fail())
    {
        cerr << "Unable to open file: " << basename << ".VES" << endl;
        return 2;
    }
    fstream vswfile((basename+".VSW").c_str());
    if (vswfile.fail())
    {
        cerr << "Unable to open file: " << basename << ".VSW" << endl;
        return 2;
    }
    ostream* out=&cout;
    if (output!="-")
    {
        out=new ofstream(output.c_str());
        if(out->fail())
        {
            cerr << "Unable to open file: " << output << endl;
        }
    }

    measurement meas(vesfile,vswfile);
    cerr << meas << endl;

    meas.writedata(*out);
    
    return 0;
}
