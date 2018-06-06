#include<iostream>
#include<fstream>
#include <sstream>
#include <string>
#include<math.h>
using namespace std;

//VARIABLE TO STORE ASSIGNMENT OF POINTS TO CENTROIDS
double assign[10][10];
int counter[10];
double pts[10000][10];//max dimension of points considered is 10

//FUNCTION TO CALCULATE DISTANCE BETWEEN EACH POINT AND CENTROID AND ASSIGN IT ACCORDINGLY
double distance(double ctr[][10],int d,int k,int index )
{
	int i,j,dim;
	double val,sum;
	val=10000;
	for(j=0;j<k;++j)
	{
		i=0;
		sum=0;
		while(i<d)
		{
			sum+=((ctr[j][i]-pts[index][i])*(ctr[j][i]-pts[index][i]));
			i++;
		}
		sum=sqrt(sum);
		if(sum<val)
		{
			val=sum;
			dim=j;
		}
	}	
	
		i=0;
		while(i<d)
		{
			assign[dim][i]+=pts[index][i];
			i++;
		}
		counter[dim]++;
}


//ENTRY TO THE PROGRAM
int main(int argc, char** argv)
{
	//ACCEPT COMMAND LINE ARGUMENTS
	string a=argv[1];
	int k=stoi(argv[2]);
	
	//REQUIRED VARIABLES
	fstream f1(a);
	string line;
	int first,dimension,n,d,i,j,l;//first refers to some initialization tasks to be done only once
	
	
	//INITIALIZATION OF VARIABLES
	first=1;
	dimension=0;
	d=0;
	n=0;
	
	
	//READ INPUT FILE AND INFER DIMENSION AND NUMBEROF
	while(getline(f1,line))
	{
		istringstream row(line);
		double field;
		d=0;
		while (row>> field)
		{
			pts[n][d]=field;
			d++;
		}
		if(first==1)
		{
			dimension=d;
			first=0;
		}
		n++;
	}
	f1.close();
	
	
	//INPUT CENTROID POINTS FROM USER
	double centroids[k][10];
	i=0;
	//cout<<"Enter "<<k<<" cluster points of "<<"dimensions"<<dimension<<":\n";
	while(i<k)
	{
		j=0; 
		//cout<<"\nCluster point number "<<i<<"\n";
		while(j<dimension)
		{
			centroids[i][j]=pts[i][j];
			j++;
		}
		i++;
	}
	
	
	//CLUSTER FORMING ITERATIONS
	bool done;//checks for updates
	int count=0;//avoids infinite looping
	while(true&&(count<15))
	{
		done=false;
		double *addr1=assign[0];
		int *addr2=counter;
		fill(addr1,addr1+100,0);
		fill(addr2,addr2+10,0);
		for(i=0;i<n;i++)
		{
			distance(centroids,dimension,k,i);
		}
		
		//LOOP TO CALCULATE NEW CLUSTER POINTS
		for(j=0;j<k;j++)
		{
			for(l=0;l<dimension;l++)
			{
				if((counter[j]!=0)&&centroids[j][l]!=(assign[j][l]/counter[j]))
				{
					centroids[j][l]=assign[j][l]/counter[j];
					done=true;
				}
			}
		}
		
		
		count++;
		if(done==true)
			continue;
		else
			break;
		
	}
	//WRITING FINAL CLUSTER POINTS TO THE FILE
	ofstream f2("cluster.txt");
	for(j=0;j<k;j++)
		{
			for(l=0;l<dimension;l++)
			{
					f2<<centroids[j][l]<<"  ";
			}
			f2<<endl;
		}
}