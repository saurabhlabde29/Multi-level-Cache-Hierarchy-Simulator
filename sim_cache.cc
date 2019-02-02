#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;
class CACHE
{
	int BLOCKSIZE;
	int SIZE;
	int ASSOC;
	int LAMBDA;
	int L2SIZE;
	std::vector<std::string> TRACESTORE;
	int NUMBEROFSETS;
	int L2NUMBEROFSETS;
	std::vector<std::string> TRACE_ADD_ONLY;
	std::vector<std::string> TRACE_R_W_TYPE;
	std::vector<std::string> TRACEADD_BIN;
	std::vector<std::vector<std::string> > TAG;
	std::vector<std::vector<std::string> > L2TAG;
	std::vector<std::string> TAGVALUE;
	std::vector<std::string> L2TAGVALUE;
	std::vector<std::string> INDEX;
	std::vector<std::string> L2INDEX;
	std::vector<std::string> BLOCKOFFSET;
	std::vector<float> DECIMAL_INDEX;
	std::vector<float> L2DECIMAL_INDEX;
	std::vector<std::vector<int> > LRUCOUNT;
	std::vector<std::vector<int> > DIRTYBIT;
	std::vector<std::vector<int> > L2DIRTYBIT;
	std::vector<std::vector<int> > VALIDBIT;
	std::vector<std::vector<int> > L2VALIDBIT;
	std::vector<std::vector<int> > LFUCOUNT;
	std::vector<std::vector<int> > L2LFUCOUNT;
	int NUMBEROFTRACEADD;
	int READCOUNT;
	int L2READCOUNT;
	int READHIT;
	int L2READHIT;
	int READMISS;
	int L2READMISS;
	int WRITECOUNT;
	int L2WRITECOUNT;
	int WRITEHIT;
	int L2WRITEHIT;
	int WRITEMISS;
	int L2WRITEMISS;
	int WRITEBACKCOUNT;
	int L2WRITEBACKCOUNT;
	int TAGVALUESIZE;
	int L2TAGVALUESIZE;
	string TRACEFILE;
	int L2ASSOC;
	int VICTIMSIZE;
	int VICTIMWRITEBACK;
	int SWAPS;
	std::vector<std::vector<long int> > TAG_DEC;
	std::vector<std::vector<int> > L2LRUCOUNT;
	public:
	CACHE (int a, int b, int c, int d, int e, std::vector<std::string> f, int g,int g1,std::vector<std::string> h,std::vector<std::string> i,std::vector<std::string> j,std::vector<std::string> l,std::vector<std::string> l1,std::vector<std::string> m,std::vector<std::string> m1,std::vector<std::string> n, std::vector<float> o,std::vector<float> o1,vector<vector<int> > p, int r,int s,int s1,string t,int u,vector<vector<int> > v,int w)
	{
		this-> BLOCKSIZE = a;
		this-> SIZE = b;
		this-> ASSOC = c;
		this-> LAMBDA = d;
		this-> L2SIZE = e;
		this-> TRACESTORE = f;
		this-> NUMBEROFSETS = g;
		this-> L2NUMBEROFSETS = g1;
		this-> TRACE_ADD_ONLY = h;
		this-> TRACE_R_W_TYPE = i;
		this-> TRACEADD_BIN = j;
		this-> TAGVALUE = l;
		this-> L2TAGVALUE = l1;
		this-> INDEX = m;
		this-> L2INDEX = m1;
		this-> BLOCKOFFSET = n;
		this-> DECIMAL_INDEX=o;
		this-> L2DECIMAL_INDEX=o1;
		this-> LRUCOUNT=p;
		this-> NUMBEROFTRACEADD=r;
		this-> TAGVALUESIZE=s;
		this-> L2TAGVALUESIZE=s1;
		this-> TRACEFILE=t;
		this-> L2ASSOC=u;
		this-> L2LRUCOUNT=v;
		this-> VICTIMSIZE=w;
		READCOUNT=0;
		L2READCOUNT=0;
		READHIT=0;
		L2READHIT=0;
		READMISS=0;
		L2READMISS=0;
		WRITECOUNT=0;
		L2WRITECOUNT=0;
		WRITEHIT=0;
		L2WRITEHIT=0;
		WRITEMISS=0;
		L2WRITEMISS=0;
		WRITEBACKCOUNT=0;
		L2WRITEBACKCOUNT=0;
		TAG.resize(g,vector<string>(c,""));
		DIRTYBIT.resize(g,vector<int>(c,0));
		L2DIRTYBIT.resize(g1,vector<int>(u,0));
		VALIDBIT.resize(g,vector<int>(c,0));
		L2VALIDBIT.resize(g1,vector<int>(u,0));
		LFUCOUNT.resize(g,vector<int>(c,0));
		TAG_DEC.resize(g,vector<long int>(c,0));
		L2TAG.resize(g1,vector<string>(u,""));
		L2LFUCOUNT.resize(g1,vector<int>(u,0));
		VICTIMWRITEBACK=0;
		SWAPS=0;
	} 
	
			int L2readfunc(int index_i)
			{	L2READCOUNT++;		
				int L2temp=0;
				int L2tempmax=0;
				int L2tempindex=0;
				int L2tempmin=0;
				int L2invalid_read=0;
				for(int j=0;j<L2ASSOC;j++)
				{ 
					if(L2TAG[L2DECIMAL_INDEX[index_i]][j]==L2TAGVALUE[index_i])
					{
						L2READHIT++;
						if(LAMBDA==2)
						{
							L2temp=L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][j]; //check j values
							for(int k=0; k<L2ASSOC ; k++)
							{
								if(L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][k]<L2temp)
								{
									L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][k]+=1;
								}
							}
							L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][j]=0;
						}
						else
						{
							L2LFUCOUNT[L2DECIMAL_INDEX[index_i]][j]++;
						}
						return 0;
					}
				}
				L2READMISS++;
				for(int j=0;j<L2ASSOC;j++)
				{
					if(L2VALIDBIT[L2DECIMAL_INDEX[index_i]][j]==0)
					{
						L2TAG[L2DECIMAL_INDEX[index_i]][j]=L2TAGVALUE[index_i];
						L2VALIDBIT[L2DECIMAL_INDEX[index_i]][j]=1;
						if(LAMBDA==2)
						{
							L2temp=L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][j];
							for(int k=0; k<L2ASSOC ; k++)
							{
								if(L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][k]<L2temp)
								{
									L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][k]+=1;
								}
							}
							L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][j]=0;
						
							L2DIRTYBIT[L2DECIMAL_INDEX[index_i]][j]=0;
						}
						else
						{
							L2LFUCOUNT[L2DECIMAL_INDEX[index_i]][j]++;				
							L2DIRTYBIT[L2DECIMAL_INDEX[index_i]][j]=0;
						}
						return 0;
					}
					else
					{
						L2invalid_read=L2invalid_read+1;
					}
				}
				if(L2invalid_read==L2ASSOC)
				{
					
					if(LAMBDA==2)
					{L2tempmax=0;
						for(int k=0;k<L2ASSOC;k++)
						{
							if(L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][k]>L2tempmax)
							{
								L2tempmax = L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][k];
								L2tempindex=k;
							}
						}
								if(L2DIRTYBIT[L2DECIMAL_INDEX[index_i]][L2tempindex]==1)
								{
									L2WRITEBACKCOUNT++;
								}
								L2DIRTYBIT[L2DECIMAL_INDEX[index_i]][L2tempindex]=0;
								L2TAG[L2DECIMAL_INDEX[index_i]][L2tempindex]=L2TAGVALUE[index_i];
							
								L2VALIDBIT[L2DECIMAL_INDEX[index_i]][L2tempindex]=1;
							
						for(int k=0;k<L2ASSOC;k++)
						{
						
							L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][k]+=1;
						
						}
							L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][L2tempindex]=0;
						
							
								
							
					}
					else
					{	L2tempmin=L2LFUCOUNT[L2DECIMAL_INDEX[index_i]][0];
						L2tempindex=0;
						for(int k=0;k<L2ASSOC;k++)
						{
							if(L2LFUCOUNT[L2DECIMAL_INDEX[index_i]][k]<L2tempmin)
							{
								L2tempmin = L2LFUCOUNT[L2DECIMAL_INDEX[index_i]][k];
								L2tempindex=k;
							}
						}
						if(L2DIRTYBIT[L2DECIMAL_INDEX[index_i]][L2tempindex]==1)
						{
							L2WRITEBACKCOUNT++;
						}
						L2DIRTYBIT[L2DECIMAL_INDEX[index_i]][L2tempindex]=0;
						L2TAG[L2DECIMAL_INDEX[index_i]][L2tempindex]=L2TAGVALUE[index_i];
						L2VALIDBIT[L2DECIMAL_INDEX[index_i]][L2tempindex]=1;
						L2LFUCOUNT[L2DECIMAL_INDEX[index_i]][L2tempindex]++;
						
						
		
					}
					
				}
			}	
				
	        int L2writefunc(int index_i, int a)
		{	L2WRITECOUNT++;	
			int L2temp=0;
			int L2tempmax=0;
			int L2tempindex=0;
			int L2tempmin=0;
			int L2invalid_write=0;
			string update;
			for(int j=0;j<L2ASSOC;j++)
				{
					if(L2TAG[L2DECIMAL_INDEX[index_i]][j]+(L2INDEX[index_i])==TAG[DECIMAL_INDEX[index_i]][a]+(INDEX[index_i]))
					{
						L2WRITEHIT++;
						if(LAMBDA==2)
						{
							L2temp=L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][j];
							for(int k=0; k<L2ASSOC ; k++)
							{
								if(L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][k]<L2temp)
								{
									L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][k]+=1;
								}
							}
							L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][j]=0;

							L2DIRTYBIT[L2DECIMAL_INDEX[index_i]][j]=1;
							
						}
						else
						{
							L2LFUCOUNT[L2DECIMAL_INDEX[index_i]][j]++;
							
							L2DIRTYBIT[L2DECIMAL_INDEX[index_i]][j]=1;
							
						}
						return 0;
					}
				}
				L2WRITEMISS++;
				
					for(int j=0;j<L2ASSOC;j++)
					{
						if(L2VALIDBIT[L2DECIMAL_INDEX[index_i]][j]==0)
						{
							update=TAG[DECIMAL_INDEX[index_i]][a]+(INDEX[index_i]);
							L2TAG[DECIMAL_INDEX[index_i]][j]=update.substr(0,L2TAGVALUESIZE);
							L2VALIDBIT[L2DECIMAL_INDEX[index_i]][j]=1;
							if(LAMBDA==2)
							{
								L2temp=L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][j];
								for(int k=0; k<L2ASSOC ; k++)
								{
									if(L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][k]<L2temp)
									{
										L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][k]+=1;
									}
								}
								L2LRUCOUNT[DECIMAL_INDEX[index_i]][j]=0;
								L2DIRTYBIT[DECIMAL_INDEX[index_i]][j]=1;
							}
							else
							{
								L2LFUCOUNT[L2DECIMAL_INDEX[index_i]][j]++;
								L2DIRTYBIT[L2DECIMAL_INDEX[index_i]][j]=1;
							}
							return 0;
						}
						else
						{
							L2invalid_write=L2invalid_write+1;
						}
					}
					if(L2invalid_write==L2ASSOC)
					{	
						
						if(LAMBDA==2)
						{L2tempmax=0;
							for(int k=0;k<L2ASSOC;k++)
							{
								if(L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][k]>L2tempmax)
								{
									L2tempmax = L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][k];
									L2tempindex=k;
								}
							}
							if(L2DIRTYBIT[L2DECIMAL_INDEX[index_i]][L2tempindex]==1 )
							{
								L2WRITEBACKCOUNT++;
							}
							L2DIRTYBIT[L2DECIMAL_INDEX[index_i]][L2tempindex]=1;
							update=TAG[DECIMAL_INDEX[index_i]][a]+(INDEX[index_i]);
							L2TAG[L2DECIMAL_INDEX[index_i]][L2tempindex]=update.substr(0,L2TAGVALUESIZE);
							L2VALIDBIT[L2DECIMAL_INDEX[index_i]][L2tempindex]=1;
						
							for(int k=0;k<ASSOC;k++)
							{
								L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][k]+=1;
							}
							L2LRUCOUNT[L2DECIMAL_INDEX[index_i]][L2tempindex]=0;
							
						}
						else
						{	L2tempindex=0;
							L2tempmin=L2LFUCOUNT[L2DECIMAL_INDEX[index_i]][0];
							for(int k=0;k<L2ASSOC;k++)
							{
								if(L2LFUCOUNT[L2DECIMAL_INDEX[index_i]][k]<L2tempmin)
								{
									L2tempmin = L2LFUCOUNT[L2DECIMAL_INDEX[index_i]][k];
									L2tempindex=k;
								}
							}
							if(L2DIRTYBIT[L2DECIMAL_INDEX[index_i]][L2tempindex]==1 )
							{
								L2WRITEBACKCOUNT++;
							}
							L2DIRTYBIT[L2DECIMAL_INDEX[index_i]][L2tempindex]=1;
							update=TAG[DECIMAL_INDEX[index_i]][a]+(INDEX[index_i]);
							L2TAG[L2DECIMAL_INDEX[index_i]][L2tempindex]=update.substr(0,L2TAGVALUESIZE);
							L2VALIDBIT[L2DECIMAL_INDEX[index_i]][L2tempindex]=1;
							L2LFUCOUNT[L2DECIMAL_INDEX[index_i]][L2tempindex]++;
							
						}
					}
		}			
	
	void operation()
	{
		int temp=0;
		int tempmax=0;
		int tempindex=0;
		int tempmin=0;
		for(int i=0;i<NUMBEROFTRACEADD;i++)
		{	int invalid_read=0;
			int invalid_write=0;
			/*****************************READ*********************************************/
			if(TRACE_R_W_TYPE[i]=="r")
			{
				READCOUNT++;

				for(int j=0;j<ASSOC;j++)
				{
					if(TAG[DECIMAL_INDEX[i]][j]==TAGVALUE[i])
					{
						READHIT++;
						if(LAMBDA==2)
						{
							temp=LRUCOUNT[DECIMAL_INDEX[i]][j];
							for(int k=0; k<ASSOC ; k++)
							{
								if(LRUCOUNT[DECIMAL_INDEX[i]][k]<temp)
								{
									LRUCOUNT[DECIMAL_INDEX[i]][k]=LRUCOUNT[DECIMAL_INDEX[i]][k]+1;
								}
							}
							LRUCOUNT[DECIMAL_INDEX[i]][j]=0;
						}
						else
						{
							LFUCOUNT[DECIMAL_INDEX[i]][j]++;
						}
						goto x;
					}
				}
				READMISS++;
				for(int j=0;j<ASSOC;j++)
				{
					if(VALIDBIT[DECIMAL_INDEX[i]][j]==0)
					{	if(L2SIZE!=0)
						{
						L2readfunc(i);
						}
						TAG[DECIMAL_INDEX[i]][j]=TAGVALUE[i];
						VALIDBIT[DECIMAL_INDEX[i]][j]=1;
						if(LAMBDA==2)
						{
							temp=LRUCOUNT[DECIMAL_INDEX[i]][j];
							for(int k=0; k<ASSOC ; k++)
							{
								if(LRUCOUNT[DECIMAL_INDEX[i]][k]<temp)
								{
									LRUCOUNT[DECIMAL_INDEX[i]][k]=LRUCOUNT[DECIMAL_INDEX[i]][k]+1;
								}
							}
							LRUCOUNT[DECIMAL_INDEX[i]][j]=0;
						
							DIRTYBIT[DECIMAL_INDEX[i]][j]=0;
						}
						else
						{
							LFUCOUNT[DECIMAL_INDEX[i]][j]++;
							
							DIRTYBIT[DECIMAL_INDEX[i]][j]=0;
						}
						goto x;
					}
					else
					{
						invalid_read=invalid_read+1;
					}
				}
				if(invalid_read==ASSOC)
				{
					tempmax=0;
					if(LAMBDA==2)
					{
						for(int k=0;k<ASSOC;k++)
						{
							if(LRUCOUNT[DECIMAL_INDEX[i]][k]>tempmax)
							{
								tempmax = LRUCOUNT[DECIMAL_INDEX[i]][k];
								tempindex=k;
							}
						}
						
							
						for(int k=0;k<ASSOC;k++)
						{
						
							LRUCOUNT[DECIMAL_INDEX[i]][k]=LRUCOUNT[DECIMAL_INDEX[i]][k]+1;
						
						}
							LRUCOUNT[DECIMAL_INDEX[i]][tempindex]=0;
						

								if(DIRTYBIT[DECIMAL_INDEX[i]][tempindex]==1)
								{
									WRITEBACKCOUNT++;
									if(L2SIZE!=0)
									{
									L2writefunc(i,tempindex);
									}
								}
								if(L2SIZE!=0)
								{
								L2readfunc(i);
								}
								DIRTYBIT[DECIMAL_INDEX[i]][tempindex]=0;
								TAG[DECIMAL_INDEX[i]][tempindex]=TAGVALUE[i];
								VALIDBIT[DECIMAL_INDEX[i]][tempindex]=1;
							
					}
					else
					{	tempmin=LFUCOUNT[DECIMAL_INDEX[i]][0];
						tempindex=0;
						for(int k=0;k<ASSOC;k++)
						{
							if(LFUCOUNT[DECIMAL_INDEX[i]][k]<tempmin)
							{
								tempmin = LFUCOUNT[DECIMAL_INDEX[i]][k];
								tempindex=k;
							}
						}
						
						if(DIRTYBIT[DECIMAL_INDEX[i]][tempindex]==1)
						{
							WRITEBACKCOUNT++;
							if(L2SIZE!=0)
							{
							L2writefunc(i,tempindex);
							}
						}
						if(L2SIZE!=0)
						{
						L2readfunc(i);
						}
						TAG[DECIMAL_INDEX[i]][tempindex]=TAGVALUE[i];
						VALIDBIT[DECIMAL_INDEX[i]][tempindex]=1;
						LFUCOUNT[DECIMAL_INDEX[i]][tempindex]++;
						DIRTYBIT[DECIMAL_INDEX[i]][tempindex]=0;
						  
					}
					
				}
				
			}
			x:;
			/******************************WRITE***************************************/
			
			if(TRACE_R_W_TYPE[i]=="w")
			{
				WRITECOUNT++;
				for(int j=0;j<ASSOC;j++)
				{
					if(TAG[DECIMAL_INDEX[i]][j]==TAGVALUE[i])
					{
						WRITEHIT++;
						if(LAMBDA==2)
						{
							temp=LRUCOUNT[DECIMAL_INDEX[i]][j];
							for(int k=0; k<ASSOC ; k++)
							{
								if(LRUCOUNT[DECIMAL_INDEX[i]][k]<temp)
								{
									LRUCOUNT[DECIMAL_INDEX[i]][k]=LRUCOUNT[DECIMAL_INDEX[i]][k]+1;
								}
							}
							LRUCOUNT[DECIMAL_INDEX[i]][j]=0;

								DIRTYBIT[DECIMAL_INDEX[i]][j]=1;
							
						}
						else
						{
							LFUCOUNT[DECIMAL_INDEX[i]][j]++;
							
								DIRTYBIT[DECIMAL_INDEX[i]][j]=1;
							
						}
						goto y;
					}
				}
				WRITEMISS++;
				
					for(int j=0;j<ASSOC;j++)
					{
						if(VALIDBIT[DECIMAL_INDEX[i]][j]==0)
						{
							if(L2SIZE!=0)
							{
							L2readfunc(i);
							}
							TAG[DECIMAL_INDEX[i]][j]=TAGVALUE[i];
							VALIDBIT[DECIMAL_INDEX[i]][j]=1;
							if(LAMBDA==2)
							{
								temp=LRUCOUNT[DECIMAL_INDEX[i]][j];
								for(int k=0; k<ASSOC ; k++)
								{
									if(LRUCOUNT[DECIMAL_INDEX[i]][k]<temp)
									{
										LRUCOUNT[DECIMAL_INDEX[i]][k]=LRUCOUNT[DECIMAL_INDEX[i]][k]+1;
									}
								}
								LRUCOUNT[DECIMAL_INDEX[i]][j]=0;
								DIRTYBIT[DECIMAL_INDEX[i]][j]=1;
							}
							else
							{
								LFUCOUNT[DECIMAL_INDEX[i]][j]++;
								DIRTYBIT[DECIMAL_INDEX[i]][j]=1;
							}
							goto y;
						}
						else
						{
							invalid_write=invalid_write+1;
						}
					}
					if(invalid_write==ASSOC)
					{	
						tempmax=0;
						if(LAMBDA==2)
						{
							for(int k=0;k<ASSOC;k++)
							{
								if(LRUCOUNT[DECIMAL_INDEX[i]][k]>tempmax)
								{
									tempmax = LRUCOUNT[DECIMAL_INDEX[i]][k];
									tempindex=k;
								}
							}
							
						
							for(int k=0;k<ASSOC;k++)
							{
								LRUCOUNT[DECIMAL_INDEX[i]][k]=LRUCOUNT[DECIMAL_INDEX[i]][k]+1;
							}
							LRUCOUNT[DECIMAL_INDEX[i]][tempindex]=0;
							if(DIRTYBIT[DECIMAL_INDEX[i]][tempindex]==1 )
							{
								WRITEBACKCOUNT++;
								if(L2SIZE!=0)
								{
								L2writefunc(i,tempindex);
								}
							}
							if(L2SIZE!=0)
							{
							L2readfunc(i);
							}
							TAG[DECIMAL_INDEX[i]][tempindex]=TAGVALUE[i];
							VALIDBIT[DECIMAL_INDEX[i]][tempindex]=1;
							DIRTYBIT[DECIMAL_INDEX[i]][tempindex]=1;
						}
						else
						{	tempindex=0;
							tempmin=LFUCOUNT[DECIMAL_INDEX[i]][0];
							for(int k=0;k<ASSOC;k++)
							{
								if(LFUCOUNT[DECIMAL_INDEX[i]][k]<tempmin)
								{
									tempmin = LFUCOUNT[DECIMAL_INDEX[i]][k];
									tempindex=k;
								}
							}
							
							if(DIRTYBIT[DECIMAL_INDEX[i]][tempindex]==1 )
							{
								WRITEBACKCOUNT++;
								if(L2SIZE!=0)
								{
								L2writefunc(i,tempindex);
								}
							}
							if(L2SIZE!=0)
							{
							L2readfunc(i);
							}
							TAG[DECIMAL_INDEX[i]][tempindex]=TAGVALUE[i];
							VALIDBIT[DECIMAL_INDEX[i]][tempindex]=1;
							LFUCOUNT[DECIMAL_INDEX[i]][tempindex]++;
							DIRTYBIT[DECIMAL_INDEX[i]][tempindex]=1;
						}
							
					
					}
				
			}
			
			y:;
		}
	}

	 void print()
	 {
		float misssum=(READMISS + WRITEMISS);
		float countsum=READCOUNT + WRITECOUNT;
		float MISSRATE=misssum/countsum;
		float L2misssum=(L2READMISS + L2WRITEMISS);
		float L2countsum=L2READCOUNT + L2WRITECOUNT;
		float L2MISSRATE=L2misssum/L2countsum;
		// int TRAFFIC;
		// if(WRITE_POLICY==0)
		// {
			// TRAFFIC=READMISS+WRITEMISS+WRITEBACKCOUNT;
		// }
		// else
		// {
			// TRAFFIC=READMISS+WRITECOUNT+WRITEBACKCOUNT;
		// }
		float HITTIME=(0.25 + (2.5 * (SIZE / 524288.0) )+ 0.025 * (BLOCKSIZE / 16.0) + (0.025 * ASSOC));
		float MISSPENALTY= ((20)+ 0.5*(BLOCKSIZE / (16.0)));
		float L2HITTIME=(0.25 + (2.5 * (L2SIZE / 524288.0) )+ 0.025 * (BLOCKSIZE / 16.0) + (0.025 * L2ASSOC));
		float AVERAGEACCESSTIME = HITTIME + MISSRATE*(L2HITTIME + L2MISSRATE * MISSPENALTY);
		cout.precision(4);
		 cout<<"===== Simulator configuration =====   "<<endl;
			cout<<"L1_BLOCKSIZE:                    "<<BLOCKSIZE<<endl;
			cout<<"L1_SIZE:                       "<<SIZE<<endl;
			cout<<"L1_ASSOC:                         "<<ASSOC<<endl;
			cout<<"Victim_Cache_Size:            "<<VICTIMSIZE<<endl;
			cout<<"L2_SIZE:                       "<<L2SIZE<<endl;
			cout<<"L2_ASSOC:                         "<<L2ASSOC<<endl;
			cout<<"trace_file:          "<<TRACEFILE<<endl;
			if(LAMBDA==2)
			{
				cout<<"Replacement Policy:           LRU"<<endl;
			}
			else
			{
				cout<<"Replacement Policy:           LFU"<<endl;
			}
			cout<<"==================================="<<endl;
			cout<<endl;
		cout<<"===== L1 contents ====="<<endl;
		for(int i=0;i<NUMBEROFSETS;i++)
		{
			cout<<"Set "<<dec<<i<<": ";
			for(int j=0;j<ASSOC;j++)
			{   
					if(DIRTYBIT[i][j]==1)
					{
					long int X = stoi(TAG[i][j],NULL,2);
					cout<<hex<<X<<" D ";
					}
					else
					{
					long int X = stoi(TAG[i][j],NULL,2);
					cout<<hex<<X<<" ";
					}
			}
			cout<<endl;
			
		}
		cout<<"===== L2 contents ====="<<endl;
		for(int i=0;i<L2NUMBEROFSETS;i++)
		{
			cout<<"Set "<<dec<<i<<": ";
			for(int j=0;j<L2ASSOC;j++)
			{   
					if(L2DIRTYBIT[i][j]==1)
					{
					long int X = stoi(L2TAG[i][j],NULL,2);
					cout<<hex<<X<<" D ";
					}
					else
					{
					long int X = stoi(L2TAG[i][j],NULL,2);
					cout<<hex<<X<<" ";
					}
			}
			cout<<endl;
			
		}
		cout<<endl;
		cout<<"====== Simulation results (raw) ======"<<endl;
		cout<<"a. number of L1 reads:           "<<dec<<READCOUNT<<endl;
		cout<<"b. number of L1 read misses:      "<<READMISS<<endl;
		cout<<"c. number of L1 writes:          "<<WRITECOUNT<<endl;
		cout<<"d. number of L1 write misses:    "<<WRITEMISS<<endl;
		cout<<"e. L1 miss rate:                "<<fixed<<MISSRATE<<endl;
		cout<<"f. number of swaps:     "<<SWAPS<<endl;
		cout<<"g. number of victim cache writeback:     "<<VICTIMWRITEBACK<<endl;
		cout<<"h. number of L2 reads:           "<<L2READCOUNT<<endl;
		cout<<"i. number of L2 read misses:     "<<L2READMISS<<endl;
		cout<<"j. number of L2 writes:          "<<L2WRITECOUNT<<endl;
		cout<<"k. number of L2 write misses:    "<<L2WRITEMISS<<endl;
		cout<<"l. L2 miss rate:                "<<L2MISSRATE<<endl;
		cout<<"m. number of L2 writeback:     "<<L2WRITEBACKCOUNT<<endl;
		//cout<<"n. total memory traffic:         "<<
		cout<<"                                  "<<endl;
		cout<<"   ==== Simulation results (performance) ===="<<endl;
		cout<<"1. average access time:           "<<fixed<<AVERAGEACCESSTIME<<" ns"<<endl;
		
	 }
}; 

 int main(int argc, char *argv[])
 {
	 using namespace std;
	 int blocksize=atoi(argv[1]); // Same for L1 and L2
	 int size=atoi(argv[2]);
	 int assoc=atoi(argv[3]);
	 int victimsize=atoi(argv[4]);
	 int lambda=atoi(argv[7]);
	 int L2size=atoi(argv[5]);
	 string tracefile=argv[8];
	 int L2assoc=atoi(argv[6]);
	 int n=0;
	 int numberofsets;
	 numberofsets=size/(blocksize*assoc);
	 int L2numberofsets = 0;
	 if(L2assoc!=0)
	 {
	 L2numberofsets=L2size/(blocksize*L2assoc); 
	 }
	 
	 int indexsize;
	 int blockoffsetsize;
	 int tagvaluesize;
	 indexsize=int(log2(numberofsets));  //number of index bits
	 blockoffsetsize=int(log2(blocksize));  // number of blockoffset bits
	 tagvaluesize=32-indexsize-blockoffsetsize;  // number of tag bits
	 int L2indexsize = 0;
	 int L2blockoffsetsize = 0;
	 int L2tagvaluesize = 0;
	 if(L2numberofsets!=0)
	 {
	 L2indexsize=int(log2(L2numberofsets));  //number of index bits for L2
	 L2blockoffsetsize=int(log2(blocksize));  // number of blockoffset bits for L2
	 L2tagvaluesize=32-L2indexsize-L2blockoffsetsize;  // number of tag bits for L2
	 }
	 // ****************************************** //
	//reading trace file 
	 std::vector<std::string> trace_store;      //defining vector to store the addresses from trace file
	 std::vector<std::string> trace_add_only(100000,""); // defining vector to store hex add only
	 std::vector<std::string> trace_r_w_type(100000,""); // defining vector to store r/w indentiifier only
	 std::vector<std::string> tagvalue(100000,"");
	 std::vector<std::string> index(100000,"");
	 std::vector<std::string> blockoffset(100000,"");
	 std::vector<std::string> L2tagvalue(100000,"");
	 std::vector<std::string> L2index(100000,"");
	 std::string line; // for getline
	 ifstream trace(argv[8]);
	 while ( std::getline(trace, line) ) // storing trace file address values into vector trace_store
	 {
        trace_store.push_back(line);
		n=n+1;
	 }
	
	 for(int i=0;i<n;i++)
	 {
		trace_add_only[i]=trace_store[i].substr(2,8);
		trace_r_w_type[i]=trace_store[i].substr(0,1);
	 }
	 for(int i=0;i<n;i++)
	 {
		 if(trace_add_only[i].length()<8)
		 {
			 trace_add_only[i].insert(0,"00");
		 }
	 }

	/************************************** HEX TO BINARY **************************************************/ 
	  std::vector<std::string> traceadd_bin(n,"");
	  std::vector<std::string> temp(n,"");
	  std::vector<std::string> L2temp(n,"");
		for(int i=0;i<n;i++)
		{	
			for(int j=0; j<=7; j++)
			{	
				switch (trace_add_only[i][j])
				{
					case '0': traceadd_bin[i].append("0000"); 
								break;
					case '1': traceadd_bin[i].append("0001"); 
								break;
					case '2': traceadd_bin[i].append("0010"); 
								break;
					case '3': traceadd_bin[i].append("0011"); 
								break;
					case '4': traceadd_bin[i].append("0100"); 
								break;
					case '5': traceadd_bin[i].append("0101"); 
								break;
					case '6': traceadd_bin[i].append("0110"); 
								break;
					case '7': traceadd_bin[i].append("0111"); 
								break;
					case '8': traceadd_bin[i].append("1000"); 
								break;
					case '9': traceadd_bin[i].append("1001"); 
								break;
					case 'a': traceadd_bin[i].append("1010"); 
								break;
					case 'b': traceadd_bin[i].append("1011"); 
								break;
					case 'c': traceadd_bin[i].append("1100");
								break;
					case 'd': traceadd_bin[i].append("1101"); 
								break;
					case 'e': traceadd_bin[i].append("1110"); 
								break;
					case 'f': traceadd_bin[i].append("1111"); 
								break;
				}
			}
			
		}

		for(int i=0;i<n;i++)        // loop to calculate arrays containg values of tags and index 
		{
			tagvalue[i]=traceadd_bin[i].substr(0,tagvaluesize);		
			temp[i]=traceadd_bin[i];
			temp[i].erase(0,tagvaluesize);
			index[i]=temp[i].substr(0,indexsize);
			L2tagvalue[i]=traceadd_bin[i].substr(0,L2tagvaluesize);		
			L2temp[i]=traceadd_bin[i];
			L2temp[i].erase(0,L2tagvaluesize);
			L2index[i]=L2temp[i].substr(0,L2indexsize);
		}
		std::vector<float> dec(n,0.0);
		std::vector<float> L2dec(n,0.0);
		int k;
		int count;
		for(int i=0; i<n; i++)    // loop to convert inde string valus to decimal values which will be used to access tag sets
		{
			count=0;
			for(k=indexsize-1; k>=0; k--)
			{
				if (index[i][k] == '1')
				{
					dec[i]+=pow(2.0,count);
					L2dec[i]+=pow(2.0,count);
				}
				count++;
			}
		}

	 
	 std::vector<std::vector<int> > LRUcount(numberofsets,std::vector <int>(assoc,0));
	 std::vector<std::vector<int> > L2LRUcount(L2numberofsets,std::vector <int>(L2assoc,0));

	 for(int i=0; i<numberofsets; i++)
	 {
	    for(int j=0; j<assoc; j++)
		{
			LRUcount[i][j]=assoc-j-1;
		}
	 }
	 for(int i=0; i<L2numberofsets; i++)
	 {
	    for(int j=0; j<L2assoc; j++)
		{
			L2LRUcount[i][j]=L2assoc-j-1;
		}
	 }
	 CACHE L1 (blocksize,size,assoc,lambda,L2size,trace_store,numberofsets,L2numberofsets,trace_add_only,trace_r_w_type,traceadd_bin,tagvalue,L2tagvalue,index,L2index,blockoffset,dec,L2dec,LRUcount,n,tagvaluesize,L2tagvaluesize,tracefile,L2assoc,L2LRUcount,victimsize);
	 L1.operation();
	 L1.print();

	 return 0;
 }