#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
	using namespace std;
	const double EPS = 1e-9;

	int valid1()
	{
	 	int x;
        		cin>>x;
        		while(std::cin.fail())
        		{
            			cout<<"\nERROR";
            			cout<<"\n reenter the value:";
           			cin.clear();
            			cin.ignore(200,'\n');
            			cin>>x;
        		}
        		return x;
	}

	double valid2()
	{
		    double x;	
		    cin>>x;
        while(cin.fail())
        {
            cout<<"\nERROR"<<endl;
            cout<<"\n reenter the value:";
            cin.clear();
            cin.ignore(265,'\n');
            cin>>x;
        }
        return x;
	}

	struct Holes
	{
	double x, y, z, r;
	Holes(){};
	Holes(bool t){
	if(t){
        cout<<"\n enter r,x,y,z";

        r=valid2();
        x=valid2();
        y=valid2();
        z=valid2();
	}
	}
	double volume(){
	return 4.0*r*r*r*(3.142) / 3.0;
	}
	bool intersects(double a){
	return z-r < a && a < z+r;
	}
	double f(double h){
	return (acos(-1)*h*h*(3.0*r-h))/3.0;
	}
	double lVolume(double p){
	double res = f(p-(z-r));
	return res;
	}
	double rVolume(double p){
	double res = f((z+r)-p);
	return res;
	}
	};


	int n, s;
	double volumeBetween(vector <Holes> &holes, double ini, double fin)
	{
		double res = 100000.0*100000.0*(fin-ini);
		double tmp = 0.0;
		for (int i = 0; i < n; i++)
		{
			tmp = 0.0;
			if (holes[i].intersects(ini))
			{
				tmp += holes[i].lVolume(ini);
			}
			if (holes[i].intersects(fin))
    			{
				tmp += holes[i].rVolume(fin);
			}
			bool contained = true;
			contained &= (ini <= holes[i].z - holes[i].r);
			contained &= (holes[i].z + holes[i].r <= fin);
			if (contained || tmp != 0.0)
			res -= (holes[i].volume() - tmp);
		}
		return res;
	}
	int main()
	{
	       	cout<<"\n enter n and s:";
		n=valid1();
		s=valid1();
		vector<Holes> holes;
		double tot = 0.0;
		for(int i = 0; i < n; i++)
    		{
			Holes s(true);
			holes.push_back(s);
			tot += s.volume();
		}
		double last = 0.0;
		double target = (100000.0*100000.0*100000.0-tot) / s;
		for (int i = 0; i < s; i++)
		{
			double ini, fin;
			ini = last;
			fin = 100000.0;
			while (fin - ini > EPS)
			{
				double mid = (ini + fin)/2;
				if (volumeBetween(holes, last, mid)<target)
				{
					ini = mid;
				}
				else
					fin = mid;
			}
			printf("%.9lf\n", (ini-last)/1000.0);
			last = ini;
		}
		return 0;
	}
