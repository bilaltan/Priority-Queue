#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>


int size = -1;


int number[42];
char* files[42] = { "content_103390154372","content_241371942532","content_275965120132","content_457408286340","content_548894379652","content_561845407364","content_563053694596","content_564021726852","content_581716971140","content_585649196676","content_589720620676","content_600347020932","content_602481462916","content_608679923332",
        "content_609140248196","content_611464941188","content_613006216836","content_613535616644","content_614351081092","content_617442086532","content_625611869828","content_627493604996","content_635974160004","content_637213838980","content_637910290052","content_639149772420","content_640072322692","content_640226922116","content_640440831620","content_640756977284",
        "content_640796167812","content_641103728260","content_642105708164","content_642921434756","content_643025047172","content_643155463812","content_643205664388","content_643773337220","content_644115500676","content_645567712900","content_646179491460","content_646599577220" };
char* docs[42] = { "Doc1","Doc2","Doc3","Doc4","Doc5","Doc6","Doc7","Doc8","Doc9","Doc10","Doc11","Doc12","Doc13","Doc14","Doc15","Doc16","Doc17","Doc18","Doc19","Doc20","Doc21","Doc22","Doc23","Doc24","Doc25","Doc26",
        "Doc27","Doc28","Doc29","Doc30","Doc31","Doc32","Doc33","Doc34","Doc35","Doc36","Doc37","Doc38","Doc39","Doc40","Doc41","Doc42" };

//Take index of node as argument and return the parent of node
int p(int i)
{

    return (i - 1) / 2;
}

//Return the left child of current node
int leftC(int i)
{

    return ((2 * i) + 1);
}

// Return the right child of current node
int rightC(int i)
{

    return ((2 * i) + 2);
}

//After collocate nodes order by Max-Heap, shift up nodes which bigger than their parents
void up(int i)
{
    int tmp = 0;
    char* dtmp;
    char* ftmp;
    while (i > 0 && number[p(i)] < number[i]) {

        //Replacement of node values
        tmp = number[p(i)];
        number[p(i)] = number[i];
        number[i] = tmp;
        // Replecament of docs elements that occur for output
        dtmp = docs[p(i)];
        docs[p(i)] = docs[i];
        docs[i] = dtmp;
        // Replacement of files elements that occur for output
        ftmp = files[p(i)];
        files[p(i)] = files[i];
        files[i] = ftmp;
      

        //Change the i value with the value come from parent
        i = p(i);
    }
}

//The function that performs scrolling operations in cases where child in the heap is less than parent
void down(int i)
{
    int max = i;
    int tmp = 0;
    char* dtmp;
    char* ftmp;
    
    int l = leftC(i);

    if (l <= size && number[l] > number[max]) {
        max = l;
    }
    
    int r = rightC(i);

    if (r <= size && number[r] > number[max]) {
        max = r;
    }

    if (i != max) {
        tmp = number[i];
        number[i] = number[max];
        number[max] = tmp;

        dtmp = docs[i];
        docs[i] = docs[max];
        docs[max] = dtmp;

        ftmp = files[i];
        files[i] = files[max];
        files[max] = ftmp;
        down(max);
    }
}

//Inserting new node for heap
void insert(int p)
{
    size = size + 1;
    number[size] = p;

    //shift up the new node
    up(size);
}

// After the Priority queue is created, the function extracted from the top node according to Max-Heap, that is, the node with the highest value.
int extractMaxHeap()
{
    int result = number[0];

    // The top node is replaced with the left node
    number[0] = number[size];
    size = size - 1;

//Shift down the element for arrange the tree
    down(0);
    return result;
}
//The function that returns the number of repetitions of the searched word
int readFile(char* filename,char* word) {

    //Determining the path and taking the file name and the word to be searched as parameters.
    FILE* filePointer;
    char* pos;
    int bufferLength = 1024;
    char buffer[1024];
    int count = 0;
    int index;
    char path[40] = "files/";
    strcat(path, filename);
    filePointer = fopen(path, "r");


    while (fgets(buffer, bufferLength, filePointer)) { //Line by line reading operations are performed within the file.
        index = 0;
        while ((pos = strstr(buffer + index, word)) != NULL) { // If the search word is found on that line, continue until you find the number of repetitions in the line.
            index = (pos - buffer) + 1;

            count++;
        }

    }
    return count;
}
//Function to print files to the screen
void printFile(char* filename) {
    FILE* filePointer;
    int bufferLength = 255;
    char buffer[255];
    int count = 0;
    char path[40] = "files/";
    strcat(path, filename);
    filePointer = fopen(path, "r");

    while (fgets(buffer, bufferLength, filePointer)) { // the file is read and printed on the screen until it reaches the end of a line
        char delim[] = "";

        char* ptr = strtok(buffer, delim);

        while (ptr != NULL)
        {
            printf("%s ", ptr);

            ptr = strtok(NULL, delim);
        }

    }
}

int main()
{

   // Char pointer created for user input
    char* word;
    word = (char*)malloc(100 * sizeof(char));

    printf("Enter a keyword: ");
    scanf("%s",word);
    char* numtmp[5];
    int doctmp[5];
    char* filetmp[5];
    char* rel;
    int i;
   //Files are read one by one and the number of searched words is added as priority queue Max-Heap
    for ( i = 0; i < 42; i++) {
        number[i] = readFile(files[i], word);
        insert(number[i]);
    }

    printf("The relevance order is: ");
    for (i = 0; i < 5; i++) {
        if (number[0] != 0) { // If the number of finds is not zero
                printf("%s(%d), ", docs[0], number[0]);
            
        }

        numtmp[i] = number[0];
        doctmp[i] = docs[0];
        filetmp[i] = files[0];
        extractMaxHeap(); // Exits most found documents
    }
    printf("\n\n");
    for ( i = 0; i < 5; i++) { //Print the top 5 documents with the most searched words
        if (numtmp[i] != 0) {
            printf("%s(%d): ", doctmp[i], numtmp[i]);
            printFile(filetmp[i]);
            printf("\n\n");
        }

    }
 
    system("pause");
    return 0;
}
