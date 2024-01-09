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
	r->RED("mcill", 100);	// 1. init
	r->RED("sec", -79);	// second customer
	r->RED("keen", 0);	// 2. invalid energy
	r->RED("right", 100);	// 3. check add right
	r->rmSeqList("right");	// 4. remove to detect new position X
	r->byeCustomer("right");
	r->RED("left", -25);	// 5. check add right
	r->RED("half", -100);	// 6. check >= MAXSIZE/2
	r->RED("same", 5);	// 7. check same RES
	r->RED("heal", 200);	// add customer
	r->RED("dupe", -45);	// 8. full table, move to queue
	r->RED("full", 12);	// add queue
	r->RED("right", 100);	// add queue
	r->RED("keen", 65);	// add queue
	r->RED("same", 23);	// 9. invalid: duplicate name
	r->RED("dina", -8);	// add queue
	r->RED("dino", -8);	// add queue
	r->RED("nana", -8);	// 10. full queue
	r->RED("flqu", 404);	// full queue
	string fileName = "test.txt";
    simulate(fileName, r);
  	delete r;
	return 0;
}
