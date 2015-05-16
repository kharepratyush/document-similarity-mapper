#include <dirent.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <map>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

typedef pair<string, double> P;

struct Order        //used for oredering of priority queue bases on value of cosine similarity
{
    bool operator()(P const &a, P const &b) const
    {
        return a.second < b.second || a.second == b.second && a.first < b.first;
    }
};

vector<string> open1(string path)       //opening any folder and saving all file-names in a vector<string>
{

    DIR    *dir;
    dirent *pdir;
    vector<string> files;

    dir = opendir(path.c_str());

    while (pdir = readdir(dir))
    {
        files.push_back(pdir->d_name);
    }

    return files;
}

bool hasEnding (string const &fullString, string const &ending)     //checking if file has a specific ending
{
    if (fullString.length() >= ending.length())
    {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    }
    else
    {
        return false;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Error";
        return 1;
    }
    vector<string> f ;
    priority_queue< P, vector<P>, Order > Q;    //priority queue for saving file name along with Similarity
    fstream file;
    map<string, int> m_query;
    string c;



    //cout<<argv[1]<<endl;
    //cout<<argv[2]<<endl;
    //cout<<argv[0]<<endl;

    /*
    argv[1] = PATH OF FOLDER
    argv[2] = PATH TO QUERY.TXT
    */

    file.open(argv[2]);  /* open and save map values of query*/

    if (file.fail())
    {
        cout << "Error!";
        file.clear( );
    }

    while (file >> c)
    {
        transform(c.begin(), c.end(), c.begin(), ::tolower);
        if ( m_query.find(c) == m_query.end() )
        {
            m_query[c] = 1;

        }
        else
        {
            m_query[c]++;
        }
    }

    map<string, int>::iterator fsd;

    double deno1; //deno1=|A|

    for ( fsd = m_query.begin(); fsd != m_query.end(); ++fsd)
        deno1 += fsd->second * fsd->second;

    //cout<<deno1<<"\n";
    if (deno1 == 0)
    {
        cout << "Empty Query\n";
        exit(0);
    }

    file.close();

    f = open1(argv[1]); // or pass which dir to open

    for (vector<string>::iterator s = f.begin(); s != f.end(); s++)
    {
        //cout<<*s<<"\n";
        if (hasEnding (*s, "txt"))
        {
            //cout << *s << "\n";

            map<string, int> m;

            string d = *s;

            d = "/test/" + d;          //address of folder containing text file
            file.open(d.c_str());



            if (file.fail())
            {
                cout << "Error!";
                file.clear( );
            }

            while (file >> c)
            {
                transform(c.begin(), c.end(), c.begin(), ::tolower);
                if ( m.find(c) == m.end() )
                {
                    m[c] = 1;

                }
                else
                {
                    m[c]++;
                }
            }
            map<string, int>::iterator fsd, fsd1;
            /*for( fsd=m.begin();fsd!=m.end();++fsd)
                cout<<fsd->first<<" "<<fsd->second<<"\n";
            */
            double sum = 0;

            /*Loop to get Cos roduct of vectors*/
            for ( fsd1 = m.begin(); fsd1 != m.end(); ++fsd1)
                for ( fsd = m_query.begin(); fsd != m_query.end(); ++fsd)
                {
                    if (fsd->first == fsd1->first)
                        sum += fsd->second * fsd1->second;
                }
            //std::cout << "Cos product: " <<  sum<< '\n';

            double deno2 = 0;

            for ( fsd = m.begin(); fsd != m.end(); ++fsd)
                deno2 += fsd->second * fsd->second;

            //cout << deno2 << "\n";
            //deno2=|B|
            double val;
            if (deno2 == 0)
                val = 0;
            else
            {
                //cout<<"Result : "<<sum/(sqrt(deno1)*sqrt(deno2))<<endl;
                val = sum / (sqrt(deno1) * sqrt(deno2));
            }
            sum = 0;



            P foo;
            foo = std::make_pair (*s, val);
            Q.push(foo);
        }
        file.close();
    }
    P foo = Q.top();
    cout << foo.first << endl; //top three results
    Q.pop();
    foo = Q.top();
    cout << foo.first << endl;
    Q.pop();
    foo = Q.top();
    cout << foo.first << endl;
    return 0;
}