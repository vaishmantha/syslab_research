#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <set>
#include <stack>
//
//	make
//	./DisplayImage mazeblue.jpg
//
using namespace cv;
using namespace std;
vector<vector<int> > val;
vector<vector<int> > maze;
class Tup {
    int r, c;
	public:
    Tup(int,int);
    int get1() const {return r;}
    int get2() const {return c;}
};
Tup dir[4] = {Tup(0,1),Tup(0,-1),Tup(1,0),Tup(-1,0)};
bool comparator(const Tup& a, const Tup& b) {
	return a.get2() > b.get2();
}
Tup::Tup (int a, int b) {
  r = a;
  c = b;
};
class direction {
    char c;
    int l;
	public:
    direction(char,int);
    char get1() const {return c;}
    int get2() const {return l;}
};
direction::direction (char a, int b) {
  c = a;
  l = b;
};
stack<Tup > queueue;
set<int> hashset;
int nearWall(int i, int j,int rows,int cols){
	int padding = 4;
	if(i<padding or i > rows-padding or j < padding or j > cols-padding){return -1;}
	int walls = 0;
	for(int ii = i-1; ii < i+2; ii++){
		for(int jj = j-1; jj < j+2; jj++){
			if(maze[ii][jj] == 888){walls++;}
		}
	}
	return walls;
}
int checkValid(int i, int j,int rows,int cols){
	if(val[i][j]>0){return 888;}
	int padding = 4;
	if(i<padding or i > rows-padding or j < padding or j > cols-padding){return 0;}
	for(int ii = i-1; ii <= i; ii++){//ii <= i+1
		for(int jj = j-1; jj <= j+1; jj++){//why does j not work
			if(val[ii][jj] > 0)
				return 888;
		}
	}
	return 0;
}
stack<Tup> dfs(Tup start, int rows, int cols, int direct,int endrow, int endcol){
	int row = start.get1();
	int col = start.get2();
	vector<Tup> rank;
	for(int d = 0; d < 4; d++){
		int heur = nearWall(row + dir[d].get1(), col + dir[d].get2(), rows, cols);
		if(direct == d){heur = heur + 1;}
		if(row+dir[d].get1() == endrow and col + dir[d].get2() == endcol){heur = heur + 10;}
		rank.push_back(Tup(d,heur));
	}
	//sort the ranks
	sort(rank.begin(), rank.end(), comparator);
	//printf("R: %d C: %d\n",row,col);
	stack<Tup> temp;
	//arbitrary end point
	if(row == endrow and col == endcol){
		stack<Tup> q;
		q.push(Tup(endrow,endcol));
		return q;
	}
	if(maze[row][col] != 0){//0 means is valid, checkvalid automatically gets rid of the outer edges
		stack<Tup> q;
		return q;
	}
	for(int i = 0; i < 4; i++){
		int newr = row + dir[rank[i].get1()].get1(); //gets tuple to get direction to get row
		int newc = col + dir[rank[i].get1()].get2();
		if(hashset.count(newc*cols+newr) == 0){
			Tup a = Tup(newr,newc);
			hashset.insert(newc*cols+newr);
			temp = dfs(a,rows,cols,rank[i].get1(),endrow,endcol);
			if(temp.size() > 0){
				temp.push(Tup(row,col));
				return temp;
			}
		}
	}
	stack<Tup> q;
	return q;
}
int main(int argc, char** argv )
{
    VideoCapture capture("bluemaze.avi");
    Mat frame;
    if( !capture.isOpened() )
        throw "Error when reading steam_avi";
	int countframe = 0;
    for( ; ; ) //  <--- figure out what that means
    {
		capture >> frame;
        if(frame.empty())
            break;
        printf("Count: %d\n" , countframe);
        if(countframe%50 == 0){
			Mat image = frame;
			imshow("asdf",image);
			waitKey(400);
			Mat filter, edge,start,end;
			//OPENCV IS BGR NOT RBG
			//blue maze: 		R: 47 	G: 69 	B: 117
			inRange(image, Scalar(60,30,30), Scalar(205,75,75), filter);
			cvtColor(filter,filter,CV_GRAY2BGR);//NEEDED to turn 3 images back into 1 !!!!!!!
			//yellow maze: 		R: 237 	G: 205 	B: 95
			//orange walls: 	R: 190 	G: 107 	B: 71
			inRange(image, Scalar(30,50,130), Scalar(90,130,230), edge);
			cvtColor(edge,edge,CV_GRAY2BGR);
			//start of maze: 	R: 92 	G: 146 	B: 64
			inRange(image, Scalar(50,100,75), Scalar(80,200,105), start);
			cvtColor(start,start,CV_GRAY2BGR);
			//end of maze: 		R: 249 	G: 59 	B: 46 and R: 150 G: 42 B: 40
			inRange(image, Scalar(25,30,150), Scalar(55,70,255), end);
			cvtColor(end,end,CV_GRAY2BGR);
			//ball: 			R: 141 	G: 23 	B: 28
			//imshow("filtered",filter);
			//waitKey(0);

			medianBlur(start, start, 7);
			//imshow("Start", start);
			//waitKey(0);

			// end working
			Mat blur = filter.clone();
			medianBlur(blur, blur, 7);
			medianBlur(blur, blur, 7);
			medianBlur(blur, blur, 7);
			//imshow("Filter", filter);
			//waitKey(0);
			//imshow("Blur", blur);
			//waitKey(0);
			medianBlur(edge, edge, 7);
			medianBlur(edge, edge, 7);
			medianBlur(edge, edge, 7);
			//imshow("Orange Edge", edge);
			//waitKey(0);
			int rows = 75;
			int cols = 100;
			double scale = ((double)(image.rows))/rows;
			double scalec = ((double)(image.cols))/cols;
			printf("%f %f\n",scale, scalec);
			printf("%d %d\n",image.rows,image.cols);
			val.assign(rows, vector<int>(cols, 0));
			double bordercut = (scalec - scale)/2.0;
			printf("%f \n", bordercut);
			for(int i = 0; i < rows; i++){
				for(int j = 0; j < cols; j++){
					int ii = (int)(i*scale);
					int jj = (int)(j*scale);
					int njj = jj + bordercut * image.cols / scalec;
					//printf("ii: %d jj: %d njj: %d\n",ii,jj,njj);
					Vec3b bgrBlue = blur.at<Vec3b>(ii, njj);
					Vec3b bgrOrange = edge.at<Vec3b>(ii, njj);
					int gray = (int)(bgrBlue[0]+bgrBlue[1]+bgrBlue[2]+bgrOrange[0]+bgrOrange[1]+bgrOrange[2]);	//add orange and filter together for total walls!!
					if(gray > 200){gray = 888;}
					if(gray == 0){
						printf(" \t");
					}else{
						printf("%d\t",gray);
					}
					val[i][j] = gray;
				}
				printf("New line \n");
			}
			maze.assign(rows, vector<int>(cols, 0));
			//for vid camera, row: 480, col: 640
			for(int i = 0; i < rows; i++) {
				for(int j = 0; j < cols; j++){
					maze[i][j] = checkValid(i,j,rows,cols);
				}
			}
			printf("Starting dfs\n");
			/*
			stack<Tup> q = dfs(Tup(9,14),rows,cols,0,58,87);
			printf("Finished dfs\n");
			int count = 0;
			int change = 1;
			int lastchange = 0;
			vector<char> path;//u d l r
			Tup prev = Tup(0,0);
			vector<direction> output;
			while (!q.empty()){
				Tup a = q.top();
				q.pop();
				if(count>0){
					if(a.get1() - prev.get1() == 1){path.push_back('d');}
					else if(a.get1() - prev.get1() == -1){path.push_back('u');}
					else if(a.get2() - prev.get2() == -1){path.push_back('l');}
					else if(a.get2() - prev.get2() ==  1){path.push_back('r');}
					else{printf("error\n");}
				}
				if(count > 1){
					if(path[path.size()-2] != path[path.size()-1]){
						change++;
						output.push_back(direction(path[path.size()-2],count-lastchange));
						lastchange = count;
					}
				}
				maze[a.get1()][a.get2()] = change;
				prev = a;
				count++;
			}
			for(int i = 0; i < rows; i++) {
				for(int j = 0; j < cols; j++){
					if(maze[i][j] == 0){printf(" \t");}
					else{printf("%d\t",maze[i][j]);}
				}
				printf("\n");
			}printf("\n\n\n");*/
		}
		countframe = countframe+1;
	}
	return(0);
}

