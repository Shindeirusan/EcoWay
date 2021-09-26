#include <iostream>
#include <fstream>
#include <locale.h>
 
using namespace std ; 

class TGraph
{
	int n ;
	int** A ;
	public:
	TGraph() ;
	void Out() ;
	int TPow(int) ;
	void GPow() ;
	void IsT() ;
	void HT() ;
	void Loop() ;
	void MEd() ;
	void Simple() ;
	void Sup() ;
	~TGraph() ;
} ;
 
TGraph::TGraph()
{
	ifstream fin("Graph.in.txt") ; 
    if (fin.is_open())
    {
	    fin >> n ;
	    A=new int*[n] ;
	    for (int i=0; i<n; i++)
        A[i]=new int[n] ; 
	    for (int i=0; i<n; i++)
	    for (int j=0; j<n; j++) A[i][j]=0 ;
	    int a, b ;
	    while ((fin >> a) && (fin >> b))
        {
            A[a-1][b-1]++ ;
            if (a!=b) A[b-1][a-1]++ ;
        }
    }
    fin.close() ; 
} 

void TGraph::Out() 
{
	ofstream fout("Graph.out.txt", std::ios::app) ;
	if (fout.is_open())
	{
		for (int i=0; i<n; i++)
		{
			bool b=false ;
			fout << i+1 << "(" ;
			for (int j=0; j<n; j++)
			for (int k=0; k<A[i][j]; k++) 
			{
				if (b) fout << ", " ; 
				else b=true ;
				fout << j+1 ;
			}
			fout << ")" << endl ;
		}
		
	    fout << endl << "   " ;
	    for (int i=0; i<n; i++)
	    {
		    if (i<9) fout << " " ;
	        fout << i+1 << " " ;
        }
	    fout << endl << "  +" ;
	    for (int i=0; i<n; i++) 
	    if (i==n-1) fout << "--" ; else fout << "---" ;
	    fout << endl ;
	    for (int i=0; i<n; i++)
	    {
		    if (i<9) fout << " " ;
		    fout << i+1 << "|" ;
		    for (int j=0; j<n; j++)
		    { 
		        if (A[i][j]<10) fout << " " ;
		        fout << A[i][j] << " "  ;
	        }	
		fout << endl ;
	    }
	    
	    int s=0, f=0 ;
	    for (int i=0; i<n; i++) s+=TPow(i) ;
	    s=s/2 ;
	    int* B=new int[s] ;
	    int* C=new int[s] ;
	    for (int i=0; i<n; i++)
	    for (int j=i; j<n; j++)
	    if (A[i][j]>0)
	    for (int k=0; k<A[i][j]; k++)
	   	{
	    	B[f]=i ;
	    	C[f]=j ;
	    	f++ ;
		}
		fout << endl << "   " ;
	    for (int i=0; i<s; i++)
	    {
	    	fout << "{" ;
		    if (B[i]<9) fout << " " ;
	        fout << B[i]+1 << "," ;
	        if (C[i]<9) fout << " " ;
	        fout << C[i]+1 << "} " ;
        }
	    fout << endl << "  +" ;
	    for (int i=0; i<s; i++) 
	    if (i==s-1) fout << "------" ; else fout << "--------" ;
	    fout << endl ;
	    for (int i=0; i<n; i++)
	    {
		    if (i<9) fout << " " ;
		    fout << i+1 << "|" ;
		    for (int j=0; j<s; j++)
		    { 
		        if ((B[j]==i) || (C[j]==i))
		        if (B[j]==C[j]) 
				{
				if (j!=0) fout << "  " ;
				fout << "     2" ;
			    }
		        else
				{
				if (j!=0) fout << "  " ;
				fout << "     1" ;
			    }
		        else 
				{
				if (j!=0) fout << "  " ;
				fout << "     0" ;
			    }
	        }	
		fout << endl ;
	    }
	    delete []B ;
	    delete []C ;
    }
    fout.close() ;
}

int TGraph::TPow(int a)
{
	int s=0 ;
	for (int i=0; i<n; i++) s+=A[a][i] ;
	return s+A[a][a] ;
}

void TGraph::GPow()
{
	ofstream fout("Graph.out.txt", std::ios::app) ;
	if (fout.is_open())
	{
		for (int i=0; i<n; i++)
		fout << "Степень вершины " << i+1 << " - " << TPow(i) << endl ;
	}
	fout.close() ;
}

void TGraph::IsT() 
{
	ofstream fout("Graph.out.txt", std::ios::app) ;
	if (fout.is_open())
	{
		fout << "Изолированные вершины: " ;
		bool b=false ;
		for (int i=0; i<n; i++)
		if (TPow(i)==0)
		{
			if (b) fout << ", " ; else b=true ;
			fout <<i+1 ; 
		} 
		fout << endl ;
	}
	fout.close() ;
}

void TGraph::HT() 
{
	ofstream fout("Graph.out.txt", std::ios::app) ;
	if (fout.is_open())
	{
		fout << "Висячие вершины: " ;
		bool b=false ;
		for (int i=0; i<n; i++)
		if (TPow(i)==1)
		{
			if (b) fout << ", " ; else b=true ;
			fout <<i+1 ; 
		} 
		fout << endl ;
	}
	fout.close() ;
}

void TGraph::Loop() 
{
	ofstream fout("Graph.out.txt", std::ios::app) ;
	if (fout.is_open())
	{
		for (int i=0; i<n; i++)
		if (A[i][i]>0) fout << "Вершина " << i+1 << " имеет петлю с кратностью " << A[i][i] << endl ;
	}
	fout.close() ;
}

void TGraph::MEd() 
{
	ofstream fout("Graph.out.txt", std::ios::app) ;
	if (fout.is_open())
	{
		for (int i=0; i<n; i++)
		for (int j=i; j<n; j++)
		if (A[i][j]>1)
		fout << "Ребро {" << i+1 << ", " << j+1 << "} - кратное, его кратность " << A[i][j] << endl ;
	}
	fout.close() ;
}

void TGraph::Simple()
{
	for(int i=0; i<n; i++)
	A[i][i]=0 ;
	for (int i=0; i<n; i++)
	for (int j=0; j<n; j++)
	if (A[i][j]>1) A[i][j]=1 ;
}

void TGraph::Sup()
{
	for (int i=0; i<n; i++)
	for (int j=0; j<n; j++)
    if (i!=j) A[i][j]=(A[i][j]+1)%2 ;
}

TGraph::~TGraph()
{
	for (int i=0; i<n; i++)
    delete []A[i] ;
}

void Clear()
{
	ofstream fout("Graph.out.txt") ;
	if (fout.is_open())
	{
		fout << "" ;
	}
	fout.close() ;
}
 
int main()
{  
    setlocale(0,"Rus") ;
	TGraph a ;
	Clear() ;
	a.Out() ;
	a.GPow() ;
	a.IsT() ;
	a.HT() ;
	a.Loop() ;
	a.MEd() ;
	a.Simple() ;
	a.Out() ;
	a.Sup() ;
	a.Out() ;
    return 0 ;
}
