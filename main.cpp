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
	r->firstCustomer("longan", 62);
	r->serveCustomer(true, "hcm", 59, "longan");
	r->serveCustomer(true, "thanhhoa", -36, "longan");
	r->serveCustomer(false, "hanoi", -29, "thanhhoa");
	r->byeCustomer("hanoi");
	r->byeCustomer("thanhhoa");
	r->byeCustomer("longan");
	r->serveCustomer(false, "cantho", 65, "hcm");
	r->byeCustomer("hcm");
	r->byeCustomer("cantho");
	string fileName = "test.txt";
    simulate(fileName, r);
  	delete r;
	return 0;
}