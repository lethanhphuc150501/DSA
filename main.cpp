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
	r->firstCustomer("half", 5);
	r->serveCustomer(true, "dump", -1, "half");
	r->serveCustomer(true, "fell", -1, "half");
	r->UNLIMITED_VOID();
	r->serveCustomer(true, "mango", -1, "half");
	r->serveCustomer(true, "ovs", -1, "half");
	r->serveCustomer(false, "dmp", -1, "half");
	r->serveCustomer(false, "fll", -1, "half");
	r->serveCustomer(false, "mngo", -1, "half");
	r->serveCustomer(false, "vs", -1, "half");
	r->serveCustomer(true, "new", 6, "dump");
	r->UNLIMITED_VOID();
	string fileName = "test.txt";
    simulate(fileName, r);
  	delete r;
	return 0;
}
