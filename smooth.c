#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main (int argc, char *argv[]){

int i=0;
int file=0;
int format=0;
int framecount=0;
double currentframe=0;
double avgframetime=0;
double sumframetimes=0;
double avgfps=0;
double lastframe=1;
double difference=0;
double abs_difference=0;
double differences=0;
double smoothness=0;
char line[255];
char filename[255];
char write[30];
char *word;
char *test;
FILE *sFile;


// check if a filename was given as argument
if(argv[1]!=NULL){file=1;}
else{printf("No file was loaded...\n");}


// check if the file is in the right format
if (file==1){
	sFile=fopen(argv[1],"r");
	if(fgets(line,sizeof line,sFile) != NULL)
	{
		word=strtok(line,",");
		
		for(i=0;i<10;i++){ word=strtok(NULL,","); }
		
		if (strcmp(word,"MsBetweenPresents")==0) {format=1;}
	}
}

//if the file is in the correct format, start processing
if(!(file==1&format==1)){ printf("The file can't be processed...\n\n'"); }
else{
	
	printf("\nPresentmon Log Smoothness Calculator v0.X by Alexandre Ziebert\n\n");
	printf("Reading File: %s\n",argv[1]);	
	
	fgets(line,sizeof line,sFile);
	word=strtok(line,",");
	for(i=0;i<10;i++){word=strtok(NULL,",");}		
	currentframe=(atof(word));
	
	difference=1;
	abs_difference=0;
	lastframe=currentframe;
	framecount++;
	
	while (fgets(line,sizeof line,sFile) != NULL){
		word=strtok(line,",");
		for(i=0;i<10;i++){word=strtok(NULL,",");}		
		currentframe=(atof(word));
		
	//	printf("Current Frame = %f ms",currentframe);		
		
		sumframetimes+=currentframe;	
			
		difference=currentframe/lastframe;
		
	//	printf("  Difference = %f",difference);
		
		if (difference < 1) { abs_difference = 1-difference; } else { abs_difference = difference-1; }
		
		differences+=abs_difference;
		
	//	printf("   abs Difference = %f\n",abs_difference);
		
		lastframe=currentframe;
		
		framecount++;
	}

	fclose(sFile);
	
	avgframetime=sumframetimes/framecount;
	avgfps=1000/avgframetime;	
	smoothness=differences/framecount;
	
	printf("%d Frames processed\n",framecount);
	
	//printf("Sum frametimes = %f\n",sumframetimes);
	
	//printf("Sum Differences = %f\n",differences);
	
	printf("Average frametime = %f ms\n",avgframetime);
	
	printf("Average FPS = %f fps\n",avgfps);
	
	//printf("Avg differences = %f\n",smoothness);
	
	printf("Smoothness = %f\n",(1-smoothness)*100);
	
}

printf("Done!\n\n");
system("pause");

}

