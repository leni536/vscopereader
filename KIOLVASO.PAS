program vscope;

var
   fajl1,fajl2,fajl3:text;
	fajlnev,path,sor,szo: string;
	xo,yo,zo,dt,xs,xk,ys,yk,zs,zk,n:real;
   i,j,s:integer;
   ch,vege:char;

begin
	writeln('Ez a program a kaotikus kettos inga meres ves es vsw fajljaibol');
	writeln('irja ki az adatokat textfajlba.');
	writeln;
	path:='d:\hallgato/';
   writeln('A jelenlegi eleresi utvonal: ',path);
	writeln('Akarsz rajta valtoztatni?');
   writeln;
   writeln('Nem valtoztatok                   n');
   writeln('Uj eleresi utvonalat adok meg     u');
   writeln('Kiegeszitem az eleresi utvonalat  k');
   writeln;
	readln(ch);
   writeln;
	if (ch = 'u') then
		begin
			write('Az uj eleresi utvonal: ');
			readln(path);
      end;

   if (ch = 'k') then
		begin
			write('Az uj eleresi utvonal: '+path);
			readln(szo);
         path:=path+szo+'/';
      end;
   repeat
   sor:='';
   writeln;
	write('Fajl neve kiterjesztes nelkul: ');
	readln(fajlnev);
   writeln;
   	assign(fajl1,path+fajlnev+'.ves');
   reset(fajl1);
	while not (sor = '"[Origin]"') do
		begin
  			readln(fajl1,sor);
  		end;
   readln(fajl1,xo);
	readln(fajl1,yo);
	xo:=xo+3;
	yo:=yo+3;
   writeln('Megtalaltam a ',path,fajlnev,'.ves fajlt es az origo adatait.');
   writeln;
	assign(fajl2,path+fajlnev+'.vsw');
	reset(fajl2);
   writeln('Megtalaltam a ',path,fajlnev,'.vsw fajlt.');
   writeln;
   assign(fajl3,path+fajlnev+'.txt');
	rewrite(fajl3);
   writeln(fajl3,'t        xsarga   xkek     ysarga   ykek');
   dt:=0.03;
   s:=8;
	for i:=1 to 9+s do readln(fajl2);
   while not eof(fajl2) do
		begin
			read(fajl2,n);
   		for j:=1 to 5 do read(fajl2,ch);
  			read(fajl2,zs);
   		for i:=1 to 5 do read(fajl2,ch);
			read(fajl2,xs);
   		for j:=1 to 5 do read(fajl2,ch);
  			read(fajl2,ys);
   		for i:=1 to 5 do read(fajl2,ch);
			read(fajl2,zk);
         for i:=1 to 5 do read(fajl2,ch);
			read(fajl2,xk);
			for i:=1 to 5 do read(fajl2,ch);
			readln(fajl2,yk);
         writeln(fajl3,(n-s)*dt:6:3,'   ',xs/10000-xo:6:3,'   ',xk/10000-xo:6:3,'   ',ys/10000-yo:6:3,'   ',yk/10000-yo:6:3);
      end;
   close(fajl3);
   writeln('Az adatokat beirtam a ',path,fajlnev,'.txt fajlba.');
   writeln;
   writeln('Akarsz mas fajlokbol is adatokat kiirni? (i/n)');
  readln(vege);
   until vege <> 'i';
end.
