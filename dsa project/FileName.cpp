#include <iomanip>
#include <iostream>
#include <limits.h>
#include <string> // Added for string data type

using namespace std;

// Number of vertices in the graph
#define V 41

// Function to get the city name
string cityName(int num) {
    string srcName;
    switch (num) {
    case 0:
        srcName = "F-7 Islamabad";
        break;
    case 1:
        srcName = "PIMS Hospital Islamabad";
        break;
    case 2:
        srcName = "F-8 Islamabad";
        break;
    case 3:
        srcName = "G-6 Islamabad";
        break;
    case 4:
        srcName = "F-6 Islamabad";
        break;
    case 5:
        srcName = "G-5 Islamabad";
        break;
    case 6:
        srcName = "F-5 Islamabad";
        break;
    case 7:
        srcName = "Fatima Jinnah Park F-9 Islamabad";
        break;
    case 8:
        srcName = "F-10 Islamabad";
        break;
    case 9:
        srcName = "F-11 Islamabad";
        break;
    case 10:
        srcName = "G-11 Islamabad";
        break;
    case 11:
        srcName = "G-10 Islamabad";
        break;
    case 12:
        srcName = "KRL Hospital Islamabad";
        break;
    case 13:
        srcName = "G-9 Islamabad";
        break;
    case 14:
        srcName = "H-8/2 Islamabad";
        break;
    case 15:
        srcName = "I-9 Islamabad";
        break;
    case 16:
        srcName = "I-8 Islamabad";
        break;
    case 17:
        srcName = "H-11 Islamabad";
        break;
    case 18:
        srcName = "H-13 Islamabad";
        break;
    case 19:
        srcName = "G-12 Islamabad";
        break;
    case 20:
        srcName = "H-8/3 Islamabad";
        break;
    case 21:
        srcName = "Shakar Parian";
        break;
    case 22:
        srcName = "E-9 Islamabad";
        break;
    case 23:
        srcName = "E-10 Islamabad";
        break;
    case 24:
        srcName = "E-8 Islamabad";
        break;
    case 25:
        srcName = "G-7 Islamabad";
        break;
    case 26:
        srcName = "Dr Irshad Hussain - Child Specialist";
        break;
    case 27:
        srcName = "G-8 Islamabad";
        break;
    case 28:
        srcName = "Shifa International Hospital";
        break;
    case 29:
        srcName = "I-10 Islamabad";
        break;
    case 30:
        srcName = "I-11 Islamabad";
        break;
    case 31:
        srcName = "PAEC General Hospital";
        break;
    case 32:
        srcName = "G-13 Islamabad";
        break;
    case 33:
        srcName = "NIH Allergy Center";
        break;
    case 34:
        srcName = "Maroof International Hospital";
        break;
    case 35:
        srcName = "Life Care International Hospital";
        break;
    case 36:
        srcName = "Noor General Hospital";
        break;
    case 37:
        srcName = "Family Health Hospital Islamabad";
        break;
    case 38:
        srcName = "Quaid-e-Azam International Hospital";
        break;
    case 39:
        srcName = "PAF Hospital Unit 2";
        break;
    case 40:
        srcName = "Ali Medical Centre";
        break;
    default:
        srcName = "Unknown";
        break;
    }
    return srcName; // return city name
}

// A function to print shortest path from source to destination
void printPath(int parent[], int j) {
    if (parent[j] == -1) //if parent array have -1 default value then return
        return;
    printPath(parent, parent[j]); //Otherwise,pick that value and recursive call for parent node 
    if (j != V)
        cout << " --> " << cityName(j);  // show city name
}

// A function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(float dist[], bool sptSet[]) {
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)  //check sptset if vertex is not marked as visited (false)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance
// array
void printSolution(float dist[], int n = V) {
    string city;
    cout << "Cities Distance from " << cityName(0) << "\n";
    for (int i = 0; i < n; i++) {
        city = cityName(i);
        cout << left << setw(15) << city << " -->\t" << dist[i] << "\n";
    }
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
void dijkstra(float graph[V][V], int src, int dest) {
    string sourceCity = cityName(src);
    float dist[V]; // The output array. dist[i] will hold the
    // shortest
// distance from src to i

    bool sptSet[V]; // sptSet[V] will be true if vertex V is
    // included in shortest
// path tree or shortest distance from src to i is
// finalized

    int parent[V];
    // Initialize all distances as INFINITE and stpSet[] as
    // false
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX, sptSet[i] = false;
        parent[i] = -1;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet[],
            // there is an edge from u to v,  (the weight of the edge is not zero).
            // and total weight of path from src to v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
    }

    // print the constructed distance array
    //printSolution(dist, V);
    cout << "Shortest path from " << sourceCity << " to " << cityName(dest) << ":\n";
    cout << sourceCity;
    printPath(parent, dest);
    cout << "\n\n --> Distance: " << dist[dest] << "\n";
}


int main()
{

    /* Let us create the example graph discussed above */
    //					       1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1
    float islamabad[V][V] = {//F-7 Islamabad 1
                                {0,4,3.2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //PIMS Hospital Islamabad 2
                                {4,0,2.5,5.2,0,0,0,5.6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                // F-8 Islamabad 3
                                {3.2,2.5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2.7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1.4},
                                //G-6 Islamabad 4
                                {0,5.2,0,0,2.8,1.7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5.2,0,0,0,2.7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //F-6  5
                                {2,0,0,2.8,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //G-5  6
                                {0,0,0,1.7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //F-5  7
                                {0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //Fatima Janah Park 8
                                {0,5.6,0,0,0,0,0,0,3.7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1.4,0,0,0,0,0,0},
                                //F-10  9
                                {0,0,0,0,0,0,0,3.7,0,1.8,0,3.1,0,0,0,0,0,0,0,0,0,0,0,3.1,0,0,0,0,0,0,0,0,0,0,2.5,0,0,0,0,0,0},
                                //F-11  10
                                {0,0,0,0,0,0,0,0,1.8,0,2.3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //G-11  11
                                {0,0,0,0,0,0,0,0,0,2.3,0,1.9,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,5.7,0,0,0,1,0,0,0,0},
                                //G-10  12
                                {0,0,0,0,0,0,0,0,3.1,0,1.9,0,3.6,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,8.6,0,0,0,1,0,0,0,0,0},
                                //KRL   13
                                {0,0,0,0,0,0,0,0,0,0,0,3.6,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //G-9  14
                                {0,0,0,0,0,0,0,0,0,0,0,0,2,0,4.3,0,0,0,0,0,0,0,0,0,0,0,1.1,2.4,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //H-8/2  15
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,4.3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2.7,0,0,0,0,0,0,0,0,0,0,0,0},
                                //I-9    16
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2.9,0,0,0,0,0,0,0,0,0,0,0,3.3,2.2,0,0,0,0,0,0,0,1.5,0,0,0},
                                //I-8  17
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2.9,0,0,0,0,0,0,0,0,0,0,0,0,1.4,0,0,0,0,0,0,0,0,0,0,0,0},
                                //H-11  18
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10.5,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                                //H-13  19
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10.5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4.8,0,0,0,0,0,4.3,0,0},
                                //G-12  20
                                {0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //H-8/3 21
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2.1,0,0,0,0,0,0,0,0,0,0,0,0},
                                //Shakar parian  22
                                {0,0,0,4.2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7.1,0,0,0,0,5.2,0,0,0,0,0,0,0},
                                //E-9  23
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4.2,2.9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2.3,0},
                                //E-10  24
                                {0,0,0,0,0,0,0,0,3.1,0,0,0,0,0,0,0,0,0,0,0,0,0,4.2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //E-8  25
                                {0,0,2.7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2.9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //G-7  26
                                {0,0,0,2.7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2.9,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //Dr Irshad  27
                                {0,0,0,0,0,0,0,0,0,0,0,3,0,1.1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //G-8  28
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,2.9,0,0,0,0,0,0,0,0,0,0,0,2.9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //Shifa Hospital 29
                                {0,0,0,0,0,0,0,0,0,0,0,0, 0,0,2.7,3.3,1.4,0, 0,0,2.1,7.1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //I-10  30
                                {0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,2.2,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 2.5,0,0,0,0,0, 0,1.8,0,0,0},
                                //I-11 31
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2.5,0,3.6,0,0,0,0,0,0,0,0,0},
                                //PAEC Hospital 32
                                {0,0,0,0,0,0,0,0,0,0,7.4,8.6,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0, 3.6,0,0,0,0,0,0,0,0,0,0},
                                //G-13  33
                                {0,0,0,0,0,0,0,0,0,0,5.7,0,0,0,0,0,0,0, 4.8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //NIH Allergy Center 34
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,5.2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //Maroof International Hospital  35
                                {0,0,0,0,0,0, 0,1.3,2.5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //Life care International Hospital  36
                                {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //Noor Genral Hospital  37
                                {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //Family Health Hospital  38
                                {0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,1.5,0,0,0,0,0,0,0,0,0,0,0,0,0,1.8,0,0,0,0,0,0,0,0,0,0,0},
                                //Quaid e azam International Hospital 39
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 4.3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //PAF Hospital Unit 2  40
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2.3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                //Ali Medical Center  41
                                {0,0,1.4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    bool flag = true;
    char runAgain;
    do
    {
        int choice, destinationChoice;

        cout << "0\t->\tF-7 Islamabad\n1\t->\tPIMS Hospital Islamabad\n2\t->\tF-8 Islamabad\n3\t->\tG-6 Islamabad\n4\t->\tF-6 Islamabad\n5\t->\tG-5 Islamabad\n6\t->\tF-5 Islamabad\n7\t->\tFatima Jinnah Park F-9 Islamabad\n8\t->\tF-10 Islamabad \n9\t->\tF-11 Islamabad \n10\t->\tG-11 Islamabad\n";
        cout << "11\t->\tG-10 Islamabad \n12\t->\tKRL Hospital Islamabad \n13\t->\tG-9 Islamabad \n14\t->\tH-8/2 Islamabad\n15\t->\tI-9 Islamabad\n16\t->\tI-8 Islamabad\n17\t->\tH-11 Islamabad\n18\t->\tH-13 Islamabad\n19\t->\tG-12 Islamabad\n20\t->\tH-8/3 Islamabad\n21\t->\tShakar Parian\n";
        cout << "22\t->\tE-9 Islamabad\n23\t->\tE-10 Islamabad\n24\t->\tE-8 Islamabad\n25\t->\t G-7 Islamabad\n26\t->\t Dr Irshad Hussain - Child Specialist\n27\t->\t G-8 Islamabad\n28\t->\tShifa International Hospital\n29\t->\t I-10 Islamabad\n30\t->\t I-11 Islamabad\n31\t->\tPAEC General Hospital\n32\t->\t G-13 Islamabad\n";
        cout << "33\t->\tNIH Allergy Center\n34\t->\t Maroof International Hospital\n35\t->\tLife Care International Hospital\n36\t->\tNoor General Hospital\n37\t->\tFamily Health Hospital Islamabad\n38\t->\tQuaid-e-Azam International Hospital\n39\t->\tPAF Hospital Unit 2\n40\t->\t Ali Medical Centre\n";
        cout << "\nChoose a  source node:";
        cin >> choice;
        cout << "Select a destination node:\n";
        cin >> destinationChoice;
        dijkstra(islamabad, choice, destinationChoice);
        system("pause");

        cout << "To run again \b press y :: ";
        cin >> runAgain;
    } while (runAgain == 'y' || runAgain == 'Y');
    return 0;
}
