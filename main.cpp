//Ivan Li QuadTree

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;
ifstream in_data1;
ofstream out_data1;
ofstream out_data2;

class image {

    public:

        int numRows, numCols, minVal, maxVal;
        int** imgAry;

        image(ifstream& data) {

            makeImgAry(data);
            loadImage(data);

            }

        ~image() {

            for(int i = 0; i < numCols; i++)
                delete [] imgAry[i];

            delete [] imgAry;

            }

        void makeImgAry(ifstream& data) {

            int num = 0;
            int count=0;

            if (data.is_open()) {

                while ( count!=4 && data>>num) {

                    if(count == 0) numRows = num;
                    else if(count == 1) numCols = num;
                    else if(count == 2) minVal = num;
                    else if(count == 3) maxVal = num;

                    count++;

                    }
                }

            imgAry = new int*[numRows]();

            for(int i = 0; i < numRows; ++i)  {

                imgAry[i] = new int[numCols]();

                }

            }


        void loadImage(ifstream& data) {

            int num ;

            if (data.is_open()) {

                for(int i=0; i<numRows; i++) {

                    for(int k=0; k<numCols; k++) {

                        while (data>>num) {

                            imgAry[i][k] = num;

                            break;

                            }
                        }
                    }
                }

            }

        void testPrint() {

            for(int i=0; i<numRows; i++) {


                for(int k=0; k<numCols; k++) {

                    out_data2<<imgAry[i][k]<<" ";

                    }

                out_data2<<endl;


                }

            out_data2<<endl;

            }


    };

class QuadTreeNode {

        friend class QuadTree;
        friend class image;

    private:

        image* myImage;
        int numRows, numCols, minVal, maxVal, color, rowOffset, colOffset;

        QuadTreeNode* NW_kid=NULL;
        QuadTreeNode* SW_kid=NULL;
        QuadTreeNode* SE_kid=NULL;
        QuadTreeNode* NE_kid=NULL;



    public:

        ~QuadTreeNode() {

            delete NW_kid;
            delete SW_kid;
            delete NE_kid;
            delete SE_kid;
            delete this;
            }


        void computeOffsets(int prowOff, int pcolOff) {

            rowOffset = prowOff;
            colOffset = pcolOff;


            }

        void computenumRowsCols(int pRows, int pCols) {


            numRows = pRows/2;
            numCols = pCols/2;


            }

        void computeColor(image* img, int rows, int cols, int rOff, int cOff) {

            int blackcount=0;
            int whitecount=0;

            for(int i=rOff; i<rOff+rows ; i++) {

                for (int j=cOff; j<cOff+cols ; j++) {

                    if(img->imgAry[i][j] == 0) whitecount++;

                    else if(img->imgAry[i][j] == 1) blackcount++;

                    }
                }

            if(blackcount==0) {
                color = 0;
                minVal = 0;
                maxVal = 0;
                }


            else if (whitecount==0) {

                color = 1;
                minVal = 1;
                maxVal = 1;

                }

            else {

                color = 2;
                minVal = 0;
                maxVal = 1;

                }


            }

        QuadTreeNode(image* img) {

            numRows = img->numRows;
            numCols = img->numCols;
            minVal = img->minVal;
            maxVal = img->maxVal;
            color = 2;
            rowOffset = 0;
            colOffset = 0;

            }

        QuadTreeNode(QuadTreeNode *T, int parent_rows, int parent_cols,
                     int parent_rowoff, int parent_coloff, image* img) {
            computenumRowsCols(parent_rows, parent_cols);
            computeOffsets(parent_rowoff, parent_coloff);
            computeColor(img, numRows, numCols, rowOffset, colOffset);

            }

        void printNode() {

            out_data1<<color<<" "<<numRows<<" "<<numCols<<" "<<minVal<<" "<<maxVal<<" "<<rowOffset<<" "<<colOffset<<" ";

            if(NW_kid==NULL) out_data1<<"X ";
            else out_data1<<NW_kid->color<<" ";

            if(SW_kid==NULL) out_data1<<"X ";
            else out_data1<<SW_kid->color<<" ";

            if(SE_kid==NULL) out_data1<<"X ";
            else out_data1<<SE_kid->color<<" ";

            if(SW_kid==NULL) out_data1<<"X ";
            else out_data1<<SW_kid->color<<" ";

            out_data1<<endl;

            }

    };

class QuadTree {

    private:

        QuadTreeNode* rootNode;
        image* myImage;

    public:



        void BuildQuadTree(QuadTreeNode *T) {

            if(T==NULL || T->color!=2) return;

            else {

                QuadTreeNode *nw = new QuadTreeNode (T, T->numRows, T->numCols, T->rowOffset,
                                                     T->colOffset , myImage);
                T->NW_kid=nw;
                BuildQuadTree(nw);

                QuadTreeNode *sw = new QuadTreeNode (T, T->numRows, T->numCols,
                                                     T->rowOffset+(T->numRows/2), T->colOffset, myImage );
                T->SW_kid=sw;
                BuildQuadTree(sw);

                QuadTreeNode *se = new QuadTreeNode (T, T->numRows, T->numCols,
                                                     T->rowOffset+T->numRows/2, T->colOffset+(T->numCols/2), myImage );
                T->SE_kid=se;
                BuildQuadTree(se);

                QuadTreeNode *ne = new QuadTreeNode (T, T->numRows, T->numCols, T->rowOffset,
                                                     T->colOffset+(T->numCols/2), myImage );
                T->NE_kid=ne;
                BuildQuadTree(ne);
                }

            }


        void PrintQuadTree(QuadTreeNode *T) {

            if(T==NULL) return;

            else {

                T->printNode();
                PrintQuadTree(T->NW_kid);
                PrintQuadTree(T->SW_kid);
                PrintQuadTree(T->SE_kid);
                PrintQuadTree(T->NE_kid);

                }

            }

        QuadTree(image* img) {

            myImage = img;
            rootNode = new QuadTreeNode(myImage);
            BuildQuadTree(rootNode);
            PrintQuadTree(rootNode);

            }

    };


int main(int argc, char * argv[]) {

    in_data1.open(argv[1]);
    out_data1.open(argv[2]);
    out_data2.open(argv[3]);

    image myImage(in_data1); //LOAD IMAGE
    myImage.testPrint();
    QuadTree myTree(&myImage);

    return 0;

    }
