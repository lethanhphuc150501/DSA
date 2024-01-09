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
	MAXSIZE = 6;
	r->RED("half", -100);
	r->RED("same", 5);
	r->RED("heal", 200);
	r->RED("dupe", -45);
	r->RED("full", 12);
	r->RED("right", 100);
	r->RED("keen", 65);
	r->RED("diff", 23);
	r->RED("dina", -8);
	r->RED("dino", -8);
	r->RED("nana", -8);
	r->RED("flqu", 404);
	r->BLUE(8);		// 1. NUM >= MAXSIZE, update queue
	r->BLUE(3);		// 2. NUM < serve_size
	r->BLUE(4);		// 3. NUM > serve_size
	string fileName = "test.txt";
    simulate(fileName, r);
  	delete r;
	return 0;
}
