#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//  function for converting decimal number n into binary and put it in string sr

void bin(int n , string &sr)
{
	if (n==0)
	{
		sr+="0";
		return;
		
	}
	if (n==1)
	{
		sr+="1";
		return;
	}
	bin(n/2,sr);       // recurrsion 
	int rm=n%2;
	string srm=to_string(rm);
	sr+=srm;
	
}




int main()
{
	string inpname;    // for input file name 
	string outname;     // for output file name 
	cout<< "input file name =";
	cin >> inpname;
	
	ifstream inpfile;
	inpfile.open(inpname.c_str(),ios::in);  //  opening file for reading the assembly instruction 
	
	cout<<"output file name=";
	cin>> outname;
	ofstream outfile;
	outfile.open(outname.c_str(),ios::out);   // opening file for writing the corresponding machine code 
	while(!inpfile.eof())
	{
		string instruction;    // for storing each instruction per line 
		getline(inpfile,instruction);
		
		   //  machine code generation if it is A-instruction 
		   
		if(instruction[0]=='@')     
		{
			string temp=instruction.substr(1,instruction.size()-1);   //slicing the decimalpart after the sign @
			int decimal=stoi(temp);  // converting that string part to integer
			string result="";   // where machine code is to be stored 
			bin(decimal,result); 
			// cout<<result;
			 // for making it a 15-bit binary code  
			for (int i=result.size();i<15;i++) 
			{
				// appending the least significant bits with 0 zeroes 
				result="0"+result;   
				
			}
			   //outputing 1 extra 0 with the above attain 15 bit binary which shows its is A instruction 
			   // and making it 16 bit (hack)  binary code 
			   
			outfile<<0<<result<<endl;
		
		}
		 // if its not A instruction than generating machine code for C instruction 
		else
		{
			string result="111";    // first there bits are reserved ones 1 as opcode in case of C instruction
			
			// now for making parts of c instruction ,i need to find the postion of =  and ; in c instruction 
			
			bool equ_find=false;  // for checking whether there is a equal sign or not in instruction  
			int equ_index;  // for finding exact postion of = sign in instruction 
			for(equ_index=0;equ_index<instruction.size();equ_index++)
			{
				if(instruction[equ_index]=='=')
				{
					equ_find=true;
					break;   // it stores the position to equ_index where = is present 
					
				}
				
			}
			
			bool semi_find=false;   // for checking whether there is a ; sign  or not in instruction 
			int semi_index;    //for finding exact postion of ; sign in instruction 
			for(semi_index=0;semi_index<instruction.size();semi_index++)
			{
				if(instruction[semi_index]==';')
				{
					semi_find=true;
					break;   // it stores the position to semi_index where ; is present
					
				}
				
			}
			
			// now finding from where  the computation part in c instruction starts and it ends
			// and slicing that portion in to the string variable 
			int cmpt_start;
			int cmpt_end;
			if(equ_find)
			{
				cmpt_start=equ_index + 1;
				
			}
			else
			{
				cmpt_start=0;
				
			}
			if(semi_find)
			{
				cmpt_end=semi_index-1;
				
			}
			else
			{
				cmpt_end=instruction.size()-1;
				
			}
			                 // COMPUTATION PART 
			    // slicing the computation part from c instruction into another variable ---- computation 
			string computation = instruction.substr(cmpt_start,cmpt_end-cmpt_start+1); 
			
			       // APPLYING CONDITIONS AND STORING THERE CORRESPONDING MACHINE CODE 
			         // first with size of 3
			if (computation[0]=='D'&&computation[1]=='+'&&computation[2]=='1')
			{
				result += "0011111";
				
			}
			
			if (computation[0]=='A'&&computation[1]=='+'&&computation[2]=='1')
			{
				result += "0110111";
				
			}
			
			if (computation[0]=='D'&&computation[1]=='-'&&computation[2]=='1')
			{
				result += "0001110";
				
			}
			
			if (computation[0]=='A'&&computation[1]=='-'&&computation[2]=='1')
			{
				result += "0110010";
				
			}
			
			if (computation[0]=='D'&&computation[1]=='+'&&computation[2]=='A')
			{
				result += "0000010";
				
			}
			
			if (computation[0]=='D'&&computation[1]=='-'&&computation[2]=='A')
			{
				result += "0010011";
				
			}
			
			if (computation[0]=='A'&&computation[1]=='-'&&computation[2]=='D')
			{
				result += "0000111";
				
			}
			
			if (computation[0]=='D'&&computation[1]=='&'&&computation[2]=='A')
			{
				result += "0000000";
				
			}
			
			if (computation[0]=='D'&&computation[1]=='|'&&computation[2]=='A')
			{
				result += "0010101";
				
			}
			
			if (computation[0]=='M'&&computation[1]=='+'&&computation[2]=='1')
			{
				result += "1110111";
				
			}
			
			if (computation[0]=='M'&&computation[1]=='-'&&computation[2]=='1')
			{
				result += "1110010";
				
			}
			if (computation[0]=='D'&&computation[1]=='+'&&computation[2]=='M')
			{
				result += "1000010";
				
			}
			
			if (computation[0]=='D'&&computation[1]=='-'&&computation[2]=='M')
			{
				result += "1010011";
				
			}
			
			if (computation[0]=='M'&&computation[1]=='-'&&computation[2]=='D')
			{
				result += "1000111";
				
			}
			
			if (computation[0]=='D'&&computation[1]=='&'&&computation[2]=='M')
			{
				result += "1000000";
				
			}
			
			if (computation[0]=='D'&&computation[1]=='|'&&computation[2]=='M')
			{
				result += "1010101";
				
			}
			    // now with size of 2
			if (computation[0]=='-'&&computation[1]=='1')
			{
				result += "0111010";
				
			}
			
			if (computation[0]=='!'&&computation[1]=='D')
			{
				result += "0001101";
				
			}
			
			if (computation[0]=='!'&&computation[1]=='A')
			{
				result += "0110001";
				
			}
			
			if (computation[0]=='-'&&computation[1]=='D')
			{
				result += "0001111";
				
			}
			
			if (computation[0]=='-'&&computation[1]=='A')
			{
				result += "0110011";
				
			}
			
			if (computation[0]=='!'&&computation[1]=='M')
			{
				result += "1110001";
				
			}
			
			if (computation[0]=='-'&&computation[1]=='M')
			{
				result += "1110011";
				
			}
			   // now with size of 1
			if (computation[0]=='0')
			{
				result += "0101010";
				
			}
			
			if (computation[0]=='1')
			{
				result += "0111111";
				
			}
			
			if (computation[0]=='D')
			{
				result += "0001100";
				
			}
			
			if (computation[0]=='A')
			{
				result += "0110000";
				
			}
			
			if (computation[0]=='M')
			{
				result += "1110000";
				
			}
			 
			                // DESTINATION  PART 
			    // slicing the  destination  part from c instruction into another variable ---- destination  
			 
			int dest_start;
			int dest_end;
			    
			        // there is a destination part only when there is equal= sign in the c instruction 
			if (equ_find)
			{
				dest_start=0;      // locating from where destination part starts 
				dest_end=equ_index-1;    // and ends 
				string destination =instruction.substr(dest_start,dest_end-dest_start+1);     // slicing destination part from c instruction 
				
				    // applying conditions for on destination sliced above part and generating thier corresponding machone code 
				       // first with size of 3
				       
				if (destination[0]=='A'&&destination[1]=='M'&&destination[2]=='D')
				{
					result +="111";
										
				}
				        // now with size of 2
				if (destination[0]=='A'&&destination[1]=='D')
				{
					result +="110";
										
				}
				
				if (destination[0]=='A'&&destination[1]=='M')
				{
					result +="101";
										
				}
				
				if (destination[0]=='M'&&destination[1]=='D')
				{
					result +="011";
										
				}
				    // now with size of 1
				if (destination[0]=='A')
				{
					result +="100";
										
				}
				
				if (destination[0]=='D')
				{
					result +="010";
										
				}
				
				if (destination[0]=='M')
				{
					result +="001";
										
				}
				
			}
			//  for c-instruction without destination part
			else
			{
				result +="000";
				
			}
			
			                 // JUMP  PART 
			    // slicing the  jump  part from c instruction into another variable ---- jump  
			 
			
			
			int jmp_start;
			int jmp_end;
			
			  // there is the jump part if there is the semi colon ; sign in the  c instruction 
			if (semi_find)
			{
				jmp_start=semi_index+1;          // locatingfrom where destination part starts 
				jmp_end=instruction.size()-1;      // and ends 
				string jump = instruction.substr(jmp_start,jmp_end-jmp_start+1);    // slicing jump part from c instruction 
				
				    // applying conditions for generating machine code for the jump sliced above part
				    
				if (jump[0]=='J'&&jump[1]=='G'&&jump[2]=='T')
				{
					result +="001";
					
				}
				
				if (jump[0]=='J'&&jump[1]=='E'&&jump[2]=='Q')
				{
					result +="010";
					
				}
				
				if (jump[0]=='J'&&jump[1]=='G'&&jump[2]=='E')
				{
					result +="011";
					
				}
				
				if (jump[0]=='J'&&jump[1]=='L'&&jump[2]=='T')
				{
					result +="100";
					
				}
				
				if (jump[0]=='J'&&jump[1]=='N'&&jump[2]=='E')
				{
					result +="101";
					
				}
				
				if (jump[0]=='J'&&jump[1]=='L'&&jump[2]=='E')
				{
					result +="110";
					
				}
				     //unconditional jump condition
				if (jump[0]=='J'&&jump[1]=='M'&&jump[2]=='P')
				{
					result +="111";
					
				}
							 
			}
			//  for no jump 
			else
			{
				result+="000";
				
			}
			
			outfile<<result<<endl;    // outputing the 16 bit machine code for the C- instruction readed from the the assembly file 
			
		}
					
		
	}	
	
		
}
