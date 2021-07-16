//Radithya Airlangga-672019007
//Tugas3 Grafika Komputer A (Asisten)
#include <GL/glut.h>
#define RATIO 1.200
#define WW 100
#define WH (WW/RATIO)
#define HALFX ((int)(WW/2))
#define HALFY ((int)(WH/2))
#define deltat .001
int WindowWidth;
int WindowHeight;

void Display() {
	glLineWidth(4.0);
	float StartShape[15][2] = {
		{-12,-12},{-12,1},{-12,1},{-4,-12},{2,-12},{-8,7},{2,7},{2,25},{-18,25}
		,{-18,19},{-18,13},{-18,-3},{-18,-12},{-18,-12},{-18,-12}
	};

	float EndShape[15] [2] = {
		{-5,-15},{0,-15},{10,-5},{15,0},{20,5},{20,10},{5,10},{-10,10},
		{-10,5},{5,5},{10,5},{0,-5}
	};
	float IntermediateShape[12][2];

	float VertexColors[12][3] = {
		{1,0,0},{1,1,0},{1,0,1},{0,1,0},{0,1,1},{0,0,1},
		{1,0.5,0},{1,0,0.5},{0.5,1,0},{0.5,0,1},{1,0,0.5},{0,1,0.5}
	}; //Pemberian Warna Tiap Titik

	static float Tween = 0.0 - deltat;//inisialisasi Nilai Tween Agar Point Pertama Benar.

	//Perulangan dibuat untuk menampung nilai Teen Tetbaru.
	if (Tween < 1) {
		Tween += deltat;
	}
	for (int Vtx = 0; Vtx < 12; Vtx++) {
		IntermediateShape[Vtx][0] = (1.0 - Tween)*StartShape[Vtx][0]
			+ Tween*EndShape[Vtx][0];
		IntermediateShape[Vtx][1] = (1.0 - Tween)*StartShape[Vtx][1]
			+ Tween*EndShape[Vtx][1];
	}


	//Setting Pointer Array  untuk titik Open GL dan Warna
	glVertexPointer(2, GL_FLOAT, 0, IntermediateShape);
	glColorPointer(3, GL_FLOAT, 0, VertexColors);

	//for (int i = 0; i < 100; i++);//Memperlambat Proses Tweening
	for (int i = 0; i < 2500000; i++);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_LINE_LOOP, 0, 12);//Membentuk Garis Loop
	glutSwapBuffers();
	glutPostRedisplay();

}

void InitGL() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-HALFX, HALFX, -HALFY, HALFY);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0, 0, 0, 0);

	glEnableClientState(GL_VERTEX_ARRAY);//Mengatur Array Titik
	glEnableClientState(GL_COLOR_ARRAY);//Mengatur Array Warna
	glShadeModel(GL_SMOOTH);
	glViewport(0, 0, WindowWidth, WindowHeight);
}

void Reshape(int w, int h) {
	glutReshapeWindow(w, (int)(w / RATIO));
	WindowWidth = w;
	WindowHeight = (int)(w / RATIO);
	InitGL();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	WindowWidth = (int)(glutGet((GLenum)GLUT_SCREEN_WIDTH) * .4);
	WindowHeight = (int)(WindowWidth / RATIO);
	glutInitWindowSize(WindowHeight, WindowHeight);
	glutInitWindowPosition((int)(glutGet((GLenum)GLUT_SCREEN_WIDTH) * .1),
		(glutGet((GLenum)GLUT_SCREEN_HEIGHT) / 2) - (WindowHeight / 2));
	glutCreateWindow("Radithya Airlangga-672019007");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	InitGL();
	glutMainLoop();
}