#include "Restaurant.cpp"
#include <fstream>

void simulate(string filename, imp_res* r)
{
	ifstream ss(filename);
	string str, maxsize, name, energy, num;
	while(ss >> str)
	{ 
		if(str == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize); 
    	}
        else if(str == "RED") // RED <NAME> <ENERGY>
        {
            ss >> name;
            ss >> energy;
            r->RED(name, stoi(energy));
    	}
    	else if(str == "BLUE") // BLUE <NUM>
    	{
                ss >> num;
    			r->BLUE(stoi(num));
		}
    	else if(str == "PURPLE") // PURPLE
    	{
    			r->PURPLE();
		}
		else if(str == "REVERSAL") // REVERSAL
		{
    			r->REVERSAL();	
		}
    	else if(str == "UNLIMITED_VOID") // UNLIMITED_VOID
     	{   	
    			r->UNLIMITED_VOID();
    	}
    	else if(str == "DOMAIN_EXPANSION") // DOMAIN_EXPANSION
    	{
    			r->DOMAIN_EXPANSION();
    	}
    	else // LIGHT <NUM>
    	{
                ss >> num;
    			r->LIGHT(stoi(num));
    	}
    }
}

int main(int argc, char* argv[]) {
	//if (argc < 2)
    //	return 1;
	//  string fileName = argv[1];
	imp_res* r = new imp_res();
	MAXSIZE = 12;
	r->RED("half", -100);
	r->RED("dump", -1);
	r->RED("same", 5);
	r->RED("heal", 200);
	r->RED("dupe", -45);
	r->RED("sami", 25);
	r->RED("sigma", -35);
	r->RED("epsilon", 45);
	r->RED("full", 12);
	r->RED("right", 100);
	r->RED("oop", -72);
	r->RED("java", -980);
	r->REVERSAL();
	r->BLUE(8);
	r->REVERSAL();
	string fileName = "test.txt";
    simulate(fileName, r);
  	delete r;
	return 0;
}
