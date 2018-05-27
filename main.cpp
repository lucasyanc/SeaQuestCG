#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>

#define PI 3.1415926535898
#define janela_altura 500
#define janela_largura 800

char plac[20];
int merX[6] = { -450, 450,-450,450,-450,450 }, merY[6], subX[6] = { -450, 450,-450,450,-450,450 }, subY[6], tubX[6] = { -450,450,-450,450,-450,450 }, tubY[6],
barcoX = -450, superficie = 0, tiroSubX[6] = { -450,450,-450,450,-450,450 }, tiroSubY[6] = { 0 }, opcaomenu = 1, opcaoSelecionada = 0;
int placar = 0, posX = 0, posY = 0, tiroX = 0, tiroY = 0, bufferY = 0, qtdtubaroes = 0, randomico = 0, qtdmergulhadores = 0,
mergulhadorescoletados = 0, vidas = 3, qtdsubmarinos = 0, mergulhadoresTotal = 0, contador = 0, contador1 = 0, contador2 = 0, pontuacaomaxima = 0, velocidade = 65;
float ang, barraoxigenio = 0;
bool esquerda = false, helice = true, tiro = false, tiroesquerda = false, tirodireita = false, perdeu = false, morreu = false, mergulhador[6] = { false },
submarinos[6] = { false }, tubaroes[6] = { false }, rodando = true, pausado = false, barco = true, barcoesquerda = true, tiroSub[6] = { false }, barrafinal = false,
trocacor = true, bonusMergulhador = false, explosaoSubmarino = false, oxigenio = false, menu = true, animaMenu = true, cor = false;

void display(void);
void animacao(int valor);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void SpecialInput(int key, int x, int y);
void Perdeu();
void Morreu();

void DesenhaTexto(char *string, int x, int y, void *fonte);
void DesenhaMiniSubmarino(int x, int y);
void DesenhaFundo();
void DesenhaSubmarino();
void DesenhaBala();
void DesenhaMergulhador(int x, int y);
void DesenhaMergulhadorD(int x, int y);
void DesenhaTubarao(int x, int y);
void DesenhaTubaraoD(int x, int y);
void DesenhaSubRival(int x, int y, int tirox, int tiroy);
void DesenhaSubRivalD(int x, int y, int tirox, int tiroy);
void DesenhaBarco(int x);
void DesenhaExplosao();
void DesenhaIcone(int x);

void animarOxigenio();
void animarHelice();
void executarTiro();
void ativarTiroSubRival();
void executarTiroSubRival();

void colocarMegulhadores();
void colocarTubaroes();
void colocarSubRival();

void animarMergulhador();
void animarTubaroes();
void animarSubRival();
void animarBarco();

void colisaoSubmarinos();
void colisaoMergulhador();
void colisaoTubarao();
void colisaoBarco();

void colisaoTiroTubarao();
void colisaoTiroSubRival();
void colisaoTiroSubRivalnoSub();

int main(int argc, char** argv) {
	setlocale(LC_ALL, "Portuguese");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(janela_largura, janela_altura);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Seaquest");
	glutReshapeFunc(tela);
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard);
	glutSpecialFunc(SpecialInput);
	glutTimerFunc(100, animacao, 1);
	glutMainLoop();
	return 0;
}

void DesenhaFundo() {
	//FUNDO 
	//FAIXA INFERIOR
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(-450, -220, 0);
	glVertex3f(450, -220, 0);
	glVertex3f(450, -250, 0);
	glVertex3f(-450, -250, 0);
	glEnd();
	glColor3f(0, 1, 0.8);
	//IMPRIME AS CREDENCIAS
	DesenhaTexto("FELIPE PERGHER", -380, -240, GLUT_BITMAP_9_BY_15);
	DesenhaTexto("SEA SUB", -30, -240, GLUT_BITMAP_9_BY_15);
	DesenhaTexto("IFC VIDEIRA", 280, -240, GLUT_BITMAP_9_BY_15);

	//FAIXA DO OXIG?NIO
	glBegin(GL_QUADS);
	glColor3f(0, 1, 1);
	glVertex3f(-450, -170, 0);
	glVertex3f(450, -170, 0);
	glVertex3f(450, -220, 0);
	glVertex3f(-450, -220, 0);
	glEnd();
	//BARRA OXIG?NIO
	glColor3f(0.24, 0.7, 0.44);
	DesenhaTexto("Oxigenio: ", -380, -199, GLUT_BITMAP_9_BY_15);
	//BARRA VERMELHA DO OXIG?NIO
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-290, -185, 0);
	glVertex3f(0, -185, 0);
	glVertex3f(0, -205, 0);
	glVertex3f(-290, -205, 0);
	glEnd();
	//BARRA CINZA DO OXIG?NIO
	glPushMatrix();
	glBegin(GL_QUADS);
	if (barrafinal == false) glColor3f(0.66, 0.66, 0.66);
	else {
		if (trocacor == true) {
			glColor3f(0.66, 0.66, 0.66);
			contador++;
			if (contador % 3 == 0) trocacor = false;
		}
		else {
			glColor3f(1, 0, 0);
			contador++;
			if (contador % 3 == 0) trocacor = true;
		}
	}
	glVertex3f(-290, -185, 0);
	glVertex3f(barraoxigenio, -185, 0);
	glVertex3f(barraoxigenio, -205, 0);
	glVertex3f(-290, -205, 0);
	glEnd();
	glPopMatrix();

	//GRAMA EM BAIXO
	glBegin(GL_QUADS);
	glColor3f(0.24, 0.7, 0.44);
	glVertex3f(-450, -155, 0);
	glVertex3f(450, -155, 0);
	glVertex3f(450, -170, 0);
	glVertex3f(-450, -170, 0);
	glEnd();

	//DEGRADE EM CIMA
	glBegin(GL_QUADS);
	glColor3f(0.96, 0.64, 0.38);
	glVertex3f(-450, 210, 0);
	glVertex3f(450, 210, 0);
	glColor3f(1, 0.46, 0.09);
	glVertex3f(450, 195, 0);
	glVertex3f(-450, 195, 0);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1, 0.55, 0);
	glVertex3f(-450, 195, 0);
	glVertex3f(450, 195, 0);
	glColor3f(1, 0.84, 0);
	glVertex3f(450, 180, 0);
	glVertex3f(-450, 180, 0);
	glEnd();
	//LINHA QUE SAI DA AGUA
	glLineWidth(3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(-450, 145, 0);
	glVertex3f(450, 145, 0);
	glEnd();
	//DEGRADE NA AGUA
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex3f(-450, 180, 0);
	glVertex3f(450, 180, 0);
	glColor3f(0, 0.75, 1);
	glVertex3f(450, 147, 0);
	glVertex3f(-450, 147, 0);
	glEnd();
	//C?U ACIMA DO DEGRADE
	glBegin(GL_QUADS);
	glColor3f(0, 1, 1);
	glVertex3f(-450, 250, 0);
	glVertex3f(450, 250, 0);
	glColor3f(0, 0, 0.8);
	glVertex3f(450, 210, 0);
	glVertex3f(-450, 210, 0);
	glEnd();
	//PLACAR
	glColor3f(0, 0, 0);
	DesenhaTexto("PONTOS: ", 100, 225, GLUT_BITMAP_9_BY_15);
	DesenhaTexto("Player 1 ", -380, 225, GLUT_BITMAP_9_BY_15);
	sprintf(plac, "%d", placar);
	DesenhaTexto(plac, 200, 225, GLUT_BITMAP_HELVETICA_12);
}
void DesenhaSubmarino() {
	//TESTA O LADO DO SUBMARINO
	if (esquerda) {
		//SUBMARINO
		//CORPO
		glPushMatrix();
		glTranslatef(posX, posY, 0);
		glColor3f(0.44, 0.5, 0.56);
		glBegin(GL_POLYGON);
		glVertex3f(-15, 10, 0);
		glVertex3f(-100, 10, 0);
		glVertex3f(-100, -2, 0);
		glVertex3f(-15, -2, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(0, 2, 0);
		glVertex3f(-85, 2, 0);
		glVertex3f(-85, -10, 0);
		glVertex3f(0, -10, 0);
		glEnd();
		//LUNETA
		glBegin(GL_POLYGON);
		glVertex3f(-45, 20, 0);
		glVertex3f(-70, 20, 0);
		glVertex3f(-70, 10, 0);
		glVertex3f(-45, 10, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-55, 23, 0);
		glVertex3f(-70, 23, 0);
		glVertex3f(-70, 20, 0);
		glVertex3f(-55, 20, 0);
		glEnd();
		//ESCOTILHA
		glLineWidth(2);
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex3f(-75, 2, 0);
		glVertex3f(-90, 2, 0);
		glEnd();
		//HELICE
		if (helice)	glColor3f(0.44, 0.5, 0.56);
		else 		glColor3f(0, 0, 1);
		glBegin(GL_QUADS);
		glVertex3f(20, 3, 0);
		glVertex3f(0, 3, 0);
		glVertex3f(0, 6, 0);
		glVertex3f(20, 6, 0);
		glEnd();

		if (helice)	glColor3f(0.44, 0.5, 0.56);
		else 		glColor3f(0, 0, 1);
		glBegin(GL_QUADS);
		glVertex3f(20, -1, 0);
		glVertex3f(0, -1, 0);
		glVertex3f(0, -5, 0);
		glVertex3f(20, -5, 0);
		glEnd();

		if (helice)	glColor3f(0.44, 0.5, 0.56);
		else 		glColor3f(0, 0, 1);
		glBegin(GL_QUADS);
		glVertex3f(20, -9, 0);
		glVertex3f(0, -9, 0);
		glVertex3f(0, -12, 0);
		glVertex3f(20, -12, 0);
		glEnd();

		if (helice == false)	glColor3f(0.44, 0.5, 0.56);
		else 		glColor3f(0, 0, 1);
		glBegin(GL_QUADS);
		glVertex3f(20, -9, 0);
		glVertex3f(0, -9, 0);
		glVertex3f(0, -5, 0);
		glVertex3f(20, -5, 0);
		glEnd();

		if (helice == false)	glColor3f(0.44, 0.5, 0.56);
		else 		glColor3f(0, 0, 1);
		glBegin(GL_QUADS);
		glVertex3f(20, -1, 0);
		glVertex3f(0, -1, 0);
		glVertex3f(0, 3, 0);
		glVertex3f(20, 3, 0);
		glEnd();
		glPopMatrix();
	}
	else {
		//SUBMARINO
		//CORPO
		glPushMatrix();
		glTranslatef(posX, posY, 0);
		glColor3f(0.47, 0.53, 0.6);
		glBegin(GL_POLYGON);
		glVertex3f(15, 10, 0);
		glVertex3f(100, 10, 0);
		glVertex3f(100, -2, 0);
		glVertex3f(15, -2, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(0, 2, 0);
		glVertex3f(85, 2, 0);
		glVertex3f(85, -10, 0);
		glVertex3f(0, -10, 0);
		glEnd();
		//LUNETA
		glBegin(GL_POLYGON);
		glVertex3f(45, 20, 0);
		glVertex3f(70, 20, 0);
		glVertex3f(70, 10, 0);
		glVertex3f(45, 10, 0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(55, 23, 0);
		glVertex3f(70, 23, 0);
		glVertex3f(70, 20, 0);
		glVertex3f(55, 20, 0);
		glEnd();
		//ESCOTILHA
		glLineWidth(2);
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex3f(75, 2, 0);
		glVertex3f(90, 2, 0);
		glEnd();
		//HELICE
		if (helice)	glColor3f(0.47, 0.53, 0.6);
		else 		glColor3f(0, 0, 1);
		glBegin(GL_QUADS);
		glVertex3f(-20, 3, 0);
		glVertex3f(0, 3, 0);
		glVertex3f(0, 6, 0);
		glVertex3f(-20, 6, 0);
		glEnd();

		if (helice)	glColor3f(0.47, 0.53, 0.6);
		else 		glColor3f(0, 0, 1);
		glBegin(GL_QUADS);
		glVertex3f(-20, -1, 0);
		glVertex3f(0, -1, 0);
		glVertex3f(0, -5, 0);
		glVertex3f(-20, -5, 0);
		glEnd();

		if (helice)	glColor3f(0.47, 0.53, 0.6);
		else 		glColor3f(0, 0, 1);
		glBegin(GL_QUADS);
		glVertex3f(-20, -9, 0);
		glVertex3f(0, -9, 0);
		glVertex3f(0, -12, 0);
		glVertex3f(-20, -12, 0);
		glEnd();

		if (helice == false)	glColor3f(0.47, 0.53, 0.6);
		else 		glColor3f(0, 0, 1);
		glBegin(GL_QUADS);
		glVertex3f(-20, -9, 0);
		glVertex3f(0, -9, 0);
		glVertex3f(0, -5, 0);
		glVertex3f(-20, -5, 0);
		glEnd();

		if (helice == false)	glColor3f(0.47, 0.53, 0.6);
		else 		glColor3f(0, 0, 1);
		glBegin(GL_QUADS);
		glVertex3f(-20, -1, 0);
		glVertex3f(0, -1, 0);
		glVertex3f(0, 3, 0);
		glVertex3f(-20, 3, 0);
		glEnd();
		glPopMatrix();
	}
}
void DesenhaBala() {
	//BALA
	glPushMatrix();
	glTranslatef(tiroX, tiroY, 0);
	glColor3f(0.7, 0.13, 0.13);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(80, 5, 0);
	glVertex3f(100, 5, 0);
	glEnd();
	glPopMatrix();
}
void DesenhaMiniSubmarino(int x, int y) {
	//SUBMARINO
	//CORPO
	glPushMatrix();
	glTranslatef(x, y, 0);
	glColor3f(1, 0.75, 0);
	glBegin(GL_POLYGON);
	glVertex3f(10, 7, 0);
	glVertex3f(40, 7, 0);
	glVertex3f(40, -2, 0);
	glVertex3f(10, -2, 0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, 2, 0);
	glVertex3f(30, 2, 0);
	glVertex3f(30, -7, 0);
	glVertex3f(0, -7, 0);
	glEnd();

	//LUNETA
	glBegin(GL_POLYGON);
	glVertex3f(25, 12, 0);
	glVertex3f(35, 12, 0);
	glVertex3f(35, 7, 0);
	glVertex3f(25, 7, 0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(30, 14, 0);
	glVertex3f(35, 14, 0);
	glVertex3f(35, 12, 0);
	glVertex3f(30, 12, 0);
	glEnd();
	//ESCOTILHA
	glLineWidth(2);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(20, 2, 0);
	glVertex3f(30, 2, 0);
	glEnd();

	//HELICE
	glBegin(GL_QUADS);
	glColor3f(1, 0.75, 0);
	glVertex3f(-5, -9, 0);
	glVertex3f(0, -9, 0);
	glVertex3f(0, 5, 0);
	glVertex3f(-5, 5, 0);
	glEnd();
	glPopMatrix();
}
void DesenhaTexto(char *string, int x, int y, void *fonte) {
	glPushMatrix();
	glRasterPos2f(x, y);
	while (*string) {
		glutBitmapCharacter(fonte, *string++);
	}
	glPopMatrix();
}
void DesenhaTubarao(int x, int y) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	//CORPO
	glBegin(GL_POLYGON_BIT);
	glColor3f(0.29, 0, 0.51);
	glVertex2f(0, 7);
	glVertex2f(30, 7);
	glVertex2f(30, 15);
	glVertex2f(0, 15);
	glEnd();
	//OLHO
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex2d(15, 14);
	glEnd();
	glColor3f(0.29, 0, 0.51);
	//BARBATANA DE CIMA
	glBegin(GL_QUADS);
	glVertex2f(7, 15);
	glVertex2f(20, 15);
	glVertex2f(20, 17);
	glVertex2f(7, 17);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(7, 17);
	glVertex2f(12, 17);
	glVertex2f(12, 19);
	glVertex2f(7, 19);
	glEnd();
	//BARBATANA DE BAIXO
	glBegin(GL_QUADS);
	glVertex2f(0, 7);
	glVertex2f(13, 7);
	glVertex2f(13, 5);
	glVertex2f(0, 5);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(0, 5);
	glVertex2f(5, 5);
	glVertex2f(5, 3);
	glVertex2f(0, 3);
	glEnd();
	//RABO
	glBegin(GL_QUADS);
	glVertex2f(0, 7);
	glVertex2f(-5, 7);
	glVertex2f(-5, 13);
	glVertex2f(0, 13);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(-5, 15);
	glVertex2f(-10, 15);
	glVertex2f(-10, 5);
	glVertex2f(-5, 5);
	glEnd();
	//PONTA DO RABO
	glBegin(GL_QUADS);
	glVertex2f(-10, 12);
	glVertex2f(-17, 12);
	glVertex2f(-17, 15);
	glVertex2f(-10, 15);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(-10, 5);
	glVertex2f(-17, 5);
	glVertex2f(-17, 8);
	glVertex2f(-10, 8);
	glEnd();

	glPopMatrix();
}
void DesenhaTubaraoD(int x, int y) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	//CORPO
	glBegin(GL_POLYGON_BIT);
	glColor3f(0.29, 0, 0.51);
	glVertex2f(0, 7);
	glVertex2f(-30, 7);
	glVertex2f(-30, 15);
	glVertex2f(0, 15);
	glEnd();
	//OLHO
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex2d(-15, 14);
	glEnd();
	glColor3f(0.29, 0, 0.51);
	//BARBATANA DE CIMA
	glBegin(GL_QUADS);
	glVertex2f(-7, 15);
	glVertex2f(-20, 15);
	glVertex2f(-20, 17);
	glVertex2f(-7, 17);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(-7, 17);
	glVertex2f(-12, 17);
	glVertex2f(-12, 19);
	glVertex2f(-7, 19);
	glEnd();
	//BARBATANA DE BAIXO
	glBegin(GL_QUADS);
	glVertex2f(0, 7);
	glVertex2f(-13, 7);
	glVertex2f(-13, 5);
	glVertex2f(0, 5);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(0, 5);
	glVertex2f(-5, 5);
	glVertex2f(-5, 3);
	glVertex2f(0, 3);
	glEnd();
	//RABO
	glBegin(GL_QUADS);
	glVertex2f(0, 7);
	glVertex2f(5, 7);
	glVertex2f(5, 13);
	glVertex2f(0, 13);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(5, 15);
	glVertex2f(10, 15);
	glVertex2f(10, 5);
	glVertex2f(5, 5);
	glEnd();
	//PONTA DO RABO
	glBegin(GL_QUADS);
	glVertex2f(10, 12);
	glVertex2f(17, 12);
	glVertex2f(17, 15);
	glVertex2f(10, 15);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(10, 5);
	glVertex2f(17, 5);
	glVertex2f(17, 8);
	glVertex2f(10, 8);
	glEnd();

	glPopMatrix();
}
void DesenhaMergulhador(int x, int y) {
	glPushMatrix();
	glLineWidth(2);
	glTranslatef(x, y, 0);
	glScaled(0.7, 0.7, 1);
	//CABE?A
	glColor3f(0.29, 0, 0.51);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 10; i++) {
		float ang = (2 * PI * i) / 10;
		glVertex2f(cos(ang) * 8, sin(ang) * 8);
	}
	glEnd();
	//CORPO
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(-20, -20);
	glEnd();
	//BRA?O DIREITO
	glBegin(GL_LINES);
	glVertex2f(-20, -12);
	glVertex2f(5, -12);
	glEnd();
	//BRA?O ESQUERDO
	glBegin(GL_LINES);
	glVertex2f(-20, -12);
	glVertex2f(-10, -20);
	glEnd();
	//PERNA DIRETA
	glBegin(GL_LINES);
	glVertex2f(-20, -20);
	glVertex2f(-22, -35);
	glEnd();
	//PERNA ESQUERDA
	glBegin(GL_LINES);
	glVertex2f(-20, -20);
	glVertex2f(-40, -25);
	glEnd();
	glPopMatrix();
}
void DesenhaMergulhadorD(int x, int y) {
	glPushMatrix();
	glLineWidth(2);
	glTranslatef(x, y, 0);
	glScaled(0.7, 0.7, 1);
	glColor3f(0.29, 0, 0.51);
	//CABE?A
	glBegin(GL_POLYGON);
	for (int i = 0; i < 10; i++) {
		float ang = (2 * PI * i) / 10;
		glVertex2f(cos(ang) * -8, sin(ang) * -8);
	}
	glEnd();
	//CORPO
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(20, -20);
	glEnd();
	//BRA?O DIREITO
	glBegin(GL_LINES);
	glVertex2f(20, -12);
	glVertex2f(-5, -12);
	glEnd();
	//BRA?O ESQUERDO
	glBegin(GL_LINES);
	glVertex2f(20, -12);
	glVertex2f(10, -20);
	glEnd();
	//PERNA DIRETA
	glBegin(GL_LINES);
	glVertex2f(20, -20);
	glVertex2f(22, -35);
	glEnd();
	//PERNA ESQUERDA
	glBegin(GL_LINES);
	glVertex2f(20, -20);
	glVertex2f(40, -25);
	glEnd();
	glPopMatrix();
}
void DesenhaSubRival(int x, int y, int tirox, int tiroy) {
	//SUBMARINO
	//CORPO
	glPushMatrix();
	glTranslatef(x, y, 0);
	glColor3f(0.18, 0.31, 0.31);
	glBegin(GL_POLYGON);
	glVertex3f(10, 7, 0);
	glVertex3f(40, 7, 0);
	glVertex3f(40, -2, 0);
	glVertex3f(10, -2, 0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, 2, 0);
	glVertex3f(30, 2, 0);
	glVertex3f(30, -7, 0);
	glVertex3f(0, -7, 0);
	glEnd();

	//LUNETA
	glBegin(GL_POLYGON);
	glVertex3f(25, 12, 0);
	glVertex3f(35, 12, 0);
	glVertex3f(35, 7, 0);
	glVertex3f(25, 7, 0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(30, 14, 0);
	glVertex3f(35, 14, 0);
	glVertex3f(35, 12, 0);
	glVertex3f(30, 12, 0);
	glEnd();
	//ESCOTILHA
	glLineWidth(2);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(20, 2, 0);
	glVertex3f(30, 2, 0);
	glEnd();

	//HELICE
	glColor3f(0.18, 0.31, 0.31);
	glBegin(GL_QUADS);
	glVertex3f(-5, -9, 0);
	glVertex3f(0, -9, 0);
	glVertex3f(0, 5, 0);
	glVertex3f(-5, 5, 0);
	glEnd();
	glPopMatrix();

	//BALA
	glPushMatrix();
	glTranslatef(tirox, tiroy, 0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3f(30, 3, 0);
	glVertex3f(40, 3, 0);
	glEnd();
	glPopMatrix();
}
void DesenhaSubRivalD(int x, int y, int tirox, int tiroy) {
	//SUBMARINO
	//CORPO
	glPushMatrix();
	glTranslatef(x, y, 0);
	glColor3f(0.18, 0.31, 0.31);
	glBegin(GL_POLYGON);
	glVertex3f(-10, 7, 0);
	glVertex3f(-40, 7, 0);
	glVertex3f(-40, -2, 0);
	glVertex3f(-10, -2, 0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, 2, 0);
	glVertex3f(-30, 2, 0);
	glVertex3f(-30, -7, 0);
	glVertex3f(0, -7, 0);
	glEnd();

	//LUNETA
	glBegin(GL_POLYGON);
	glVertex3f(-25, 12, 0);
	glVertex3f(-35, 12, 0);
	glVertex3f(-35, 7, 0);
	glVertex3f(-25, 7, 0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-30, 14, 0);
	glVertex3f(-35, 14, 0);
	glVertex3f(-35, 12, 0);
	glVertex3f(-30, 12, 0);
	glEnd();
	//ESCOTILHA
	glLineWidth(2);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(-20, 2, 0);
	glVertex3f(-30, 2, 0);
	glEnd();

	//HELICE
	glColor3f(0.18, 0.31, 0.31);
	glBegin(GL_QUADS);
	glVertex3f(5, -9, 0);
	glVertex3f(0, -9, 0);
	glVertex3f(0, 5, 0);
	glVertex3f(5, 5, 0);
	glEnd();
	glPopMatrix();

	//BALA
	glPushMatrix();
	glTranslatef(tirox, tiroy, 0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3f(-30, 3, 0);
	glVertex3f(-40, 3, 0);
	glEnd();
	glPopMatrix();
}
void DesenhaBarco(int x) {
	glPushMatrix();
	glTranslatef(x, 0, 0);
	//CORPO
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(0, 162);
	glVertex2f(50, 162);
	glVertex2f(40, 150);
	glVertex2f(10, 150);
	glEnd();
	//MASTRO
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex2f(15, 162);
	glVertex2f(16, 162);
	glVertex2f(16, 185);
	glVertex2f(15, 185);
	glEnd();
	//VELA
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(15, 170);
	glVertex2f(35, 170);
	glVertex2f(15, 185);
	glEnd();
	glPopMatrix();
}
void DesenhaExplosao() {
	if (esquerda) {
		//PRIMEIRO POLIGONO
		glPushMatrix();
		if (cor == true) glColor3f(1, 0, 0);
		else glColor3f(1, 1, 0);
		glLineWidth(7);
		glTranslatef(-60, 0, 0);
		glTranslatef(posX, posY, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(0, 40);
		glVertex2f(20, 10);
		glVertex2f(60, 60);
		glVertex2f(50, 20);
		glVertex2f(80, 40);
		glVertex2f(70, 5);
		glVertex2f(100, 5);
		glVertex2f(70, -10);
		glVertex2f(115, -20);
		glVertex2f(60, -30);
		glVertex2f(70, -55);
		glVertex2f(30, -40);
		glVertex2f(10, -60);
		glVertex2f(0, -35);
		glVertex2f(-20, -65);
		glVertex2f(-15, -30);
		glVertex2f(-60, -20);
		glVertex2f(-15, -5);
		glVertex2f(-50, 20);
		glVertex2f(-10, 10);
		glVertex2f(0, 40);
		glEnd();

		//SEGUNDO POLIGONO
		if (cor == false) glColor3f(1, 0, 0);
		else glColor3f(1, 1, 0);
		glLineWidth(7);
		glBegin(GL_LINE_LOOP);
		glVertex2f(0, 30);
		glVertex2f(10, 0);
		glVertex2f(50, 50);
		glVertex2f(40, 10);
		glVertex2f(70, 30);
		glVertex2f(60, 0);
		glVertex2f(90, 0);
		glVertex2f(60, 0);
		glVertex2f(105, -10);
		glVertex2f(50, -20);
		glVertex2f(60, -45);
		glVertex2f(20, -30);
		glVertex2f(0, -50);
		glVertex2f(0, -25);
		glVertex2f(-10, -55);
		glVertex2f(-5, -20);
		glVertex2f(-50, -10);
		glVertex2f(-5, 0);
		glVertex2f(-40, 10);
		glVertex2f(0, 0);
		glVertex2f(0, 30);
		glEnd();

		//TERCEIRO POLIGONO
		if (cor == true) glColor3f(1, 0, 0);
		else glColor3f(1, 1, 0);
		glLineWidth(7);
		glBegin(GL_LINE_LOOP);
		glVertex2f(0, 20);
		glVertex2f(0, 0);
		glVertex2f(40, 40);
		glVertex2f(30, 0);
		glVertex2f(60, 20);
		glVertex2f(50, 0);
		glVertex2f(80, 0);
		glVertex2f(50, 0);
		glVertex2f(95, 0);
		glVertex2f(40, -10);
		glVertex2f(50, -35);
		glVertex2f(10, -20);
		glVertex2f(0, -40);
		glVertex2f(0, -15);
		glVertex2f(0, -45);
		glVertex2f(0, -10);
		glVertex2f(-40, 0);
		glVertex2f(0, 0);
		glVertex2f(-30, 0);
		glVertex2f(0, 0);
		glVertex2f(0, 20);
		glEnd();

		//QUARTO POLIGONO
		if (cor == false) glColor3f(1, 0, 0);
		else glColor3f(1, 1, 0);
		glLineWidth(7);
		glBegin(GL_LINE_LOOP);
		glVertex2f(0, 10);
		glVertex2f(0, 0);
		glVertex2f(30, 30);
		glVertex2f(20, 0);
		glVertex2f(50, 10);
		glVertex2f(40, 0);
		glVertex2f(70, 0);
		glVertex2f(40, 0);
		glVertex2f(85, 0);
		glVertex2f(30, 0);
		glVertex2f(40, -25);
		glVertex2f(0, -10);
		glVertex2f(0, -30);
		glVertex2f(0, -5);
		glVertex2f(0, -35);
		glVertex2f(0, 0);
		glVertex2f(-30, 0);
		glVertex2f(0, 0);
		glVertex2f(-20, 0);
		glVertex2f(0, 0);
		glVertex2f(0, 10);
		glEnd();
		glPopMatrix();
	}
	else {
		//PRIMEIRO POLIGONO
		glPushMatrix();
		if (cor == true) glColor3f(1, 0, 0);
		else glColor3f(1, 1, 0);
		glLineWidth(7);
		glTranslatef(posX, posY, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(0, 40);
		glVertex2f(20, 10);
		glVertex2f(60, 60);
		glVertex2f(50, 20);
		glVertex2f(80, 40);
		glVertex2f(70, 5);
		glVertex2f(100, 5);
		glVertex2f(70, -10);
		glVertex2f(115, -20);
		glVertex2f(60, -30);
		glVertex2f(70, -55);
		glVertex2f(30, -40);
		glVertex2f(10, -60);
		glVertex2f(0, -35);
		glVertex2f(-20, -65);
		glVertex2f(-15, -30);
		glVertex2f(-60, -20);
		glVertex2f(-15, -5);
		glVertex2f(-50, 20);
		glVertex2f(-10, 10);
		glVertex2f(0, 40);
		glEnd();

		//SEGUNDO POLIGONO
		if (cor == false) glColor3f(1, 0, 0);
		else glColor3f(1, 1, 0);
		glLineWidth(7);
		glBegin(GL_LINE_LOOP);
		glVertex2f(0, 30);
		glVertex2f(10, 0);
		glVertex2f(50, 50);
		glVertex2f(40, 10);
		glVertex2f(70, 30);
		glVertex2f(60, 0);
		glVertex2f(90, 0);
		glVertex2f(60, 0);
		glVertex2f(105, -10);
		glVertex2f(50, -20);
		glVertex2f(60, -45);
		glVertex2f(20, -30);
		glVertex2f(0, -50);
		glVertex2f(0, -25);
		glVertex2f(-10, -55);
		glVertex2f(-5, -20);
		glVertex2f(-50, -10);
		glVertex2f(-5, 0);
		glVertex2f(-40, 10);
		glVertex2f(0, 0);
		glVertex2f(0, 30);
		glEnd();

		//TERCEIRO POLIGONO
		if (cor == true) glColor3f(1, 0, 0);
		else glColor3f(1, 1, 0);
		glLineWidth(7);
		glBegin(GL_LINE_LOOP);
		glVertex2f(0, 20);
		glVertex2f(0, 0);
		glVertex2f(40, 40);
		glVertex2f(30, 0);
		glVertex2f(60, 20);
		glVertex2f(50, 0);
		glVertex2f(80, 0);
		glVertex2f(50, 0);
		glVertex2f(95, 0);
		glVertex2f(40, -10);
		glVertex2f(50, -35);
		glVertex2f(10, -20);
		glVertex2f(0, -40);
		glVertex2f(0, -15);
		glVertex2f(0, -45);
		glVertex2f(0, -10);
		glVertex2f(-40, 0);
		glVertex2f(0, 0);
		glVertex2f(-30, 0);
		glVertex2f(0, 0);
		glVertex2f(0, 20);
		glEnd();

		//QUARTO POLIGONO
		if (cor == false) glColor3f(1, 0, 0);
		else glColor3f(1, 1, 0);
		glLineWidth(7);
		glBegin(GL_LINE_LOOP);
		glVertex2f(0, 10);
		glVertex2f(0, 0);
		glVertex2f(30, 30);
		glVertex2f(20, 0);
		glVertex2f(50, 10);
		glVertex2f(40, 0);
		glVertex2f(70, 0);
		glVertex2f(40, 0);
		glVertex2f(85, 0);
		glVertex2f(30, 0);
		glVertex2f(40, -25);
		glVertex2f(0, -10);
		glVertex2f(0, -30);
		glVertex2f(0, -5);
		glVertex2f(0, -35);
		glVertex2f(0, 0);
		glVertex2f(-30, 0);
		glVertex2f(0, 0);
		glVertex2f(-20, 0);
		glVertex2f(0, 0);
		glVertex2f(0, 10);
		glEnd();
		glPopMatrix();
	}
}
void DesenhaIcone(int x) {
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(-75, x, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 7);
	glVertex2f(0, -7);
	glVertex2f(30, 0);
	glEnd();
	glPopMatrix();
}

void animarOxigenio() {
	//ANIMAR A BARRA DE OXIG?NIO
	if (barraoxigenio < -200) barrafinal = true;
	else barrafinal = false;

	if (posY < 160) {
		if (barraoxigenio > -290) {
			barraoxigenio -= 0.5;

		}
		else {
			explosaoSubmarino = true;
			barrafinal = false;
			barraoxigenio += 290;
		}
	}
	else {
		superficie++;
		if (superficie % 30 == 0 && mergulhadorescoletados >= 1) {
			mergulhadorescoletados--;
		}
		if (mergulhadorescoletados == 8) {
			bonusMergulhador = true;
			rodando = false;
		}
		if (barraoxigenio < 0) {
			barraoxigenio += 10;
			if (barraoxigenio > 0) barraoxigenio = 0;
		}
	}
}
void animarHelice() {
	//ANIMAR A H?LICE
	if (helice) helice = false;
	else helice = true;
}

void colocarMegulhadores() {
	//COLOCA OS MERGULHADORES NA TELA E COLOCA O BARCO
	randomico = rand() % 45;
	if (randomico == 0) {
		//S? CHAMA MERGULHADOR SE TIVER MENOS QUE 6 ATIVOS
		if (qtdmergulhadores < 6) {
			mergulhadoresTotal++;
			//DIMINUI 1 MERGULHADOR A CADA 10 MERGULHADORES 
			if (mergulhadoresTotal % 10 == 0) mergulhadorescoletados--;
			//COLOCA O BARCO ATIVO A CADA 5 MERGULHADORES QUE PASSAREM
			if (mergulhadoresTotal % 5 == 0) barco = true;

			qtdmergulhadores++;
			//SE O MERGULHADOR 0 ESTA FORA ELE ? CHAMADO
			if (mergulhador[0] == false) {
				mergulhador[0] = true;
				//OBTEM UM VALOR PARA O Y DO MERGULHADOR DE -140 AT? 140
				srand((unsigned)time(NULL));
				merY[0] = (rand() % 280) - 140;
			}
			//SE O MERGULHADOR 1 ESTA FORA ELE ? CHAMADO
			else if (mergulhador[1] == false) {
				mergulhador[1] = true;
				merY[1] = (rand() % 280) - 140;
			}
			//SE O MERGULHADOR 2 ESTA FORA ELE ? CHAMADO
			else if (mergulhador[2] == false) {
				mergulhador[2] = true;
				merY[2] = (rand() % 280) - 140;
			}
			//SE O MERGULHADOR 3 ESTA FORA ELE ? CHAMADO
			else if (mergulhador[3] == false) {
				mergulhador[3] = true;
				merY[3] = (rand() % 280) - 140;
			}
			//SE O MERGULHADOR 4 ESTA FORA ELE ? CHAMADO
			else if (mergulhador[4] == false) {
				mergulhador[4] = true;
				merY[4] = (rand() % 280) - 140;
			}
			//SE O MERGULHADOR 5 ESTA FORA ELE ? CHAMADO
			else if (mergulhador[5] == false) {
				mergulhador[5] = true;
				merY[5] = (rand() % 280) - 140;
			}
		}
	}
}
void colocarTubaroes() {
	//COLOCA OS TUBAR?ES NA TELA
	randomico = rand() % 40;
	if (randomico == 0) {
		//S? CHAMA TUBARAO SE TIVER MENOS QUE 6 ATIVOS
		if (qtdtubaroes < 6) {
			qtdtubaroes++;
			//SE O TUBARAO 0 ESTA FORA ELE ? CHAMADO
			if (tubaroes[0] == false) {
				tubaroes[0] = true;
				//OBTEM UM VALOR PARA O Y DO SUBMARINO DE -140 AT? 140
				srand((unsigned)time(NULL));
				tubY[0] = (rand() % 280) - 150;
				while (tubY[0] % 10 != 0) {
					tubY[0] = (rand() % 280) - 150;
				}
				tubY[0] += 13;
			}
			//SE O TUBARAO 1 ESTA FORA ELE ? CHAMADO
			else if (tubaroes[1] == false) {
				tubaroes[1] = true;
				tubY[1] = (rand() % 280) - 150;
				while (tubY[1] % 10 != 0) {
					tubY[1] = (rand() % 280) - 150;
				}
				tubY[1] += 13;
			}
			//SE O TUBARAO 2 ESTA FORA ELE ? CHAMADO
			else if (tubaroes[2] == false) {
				tubaroes[2] = true;
				tubY[2] = (rand() % 280) - 150;
				while (tubY[2] % 10 != 0) {
					tubY[2] = (rand() % 280) - 150;
				}
				tubY[2] += 13;
			}
			//SE O TUBARAO 3 ESTA FORA ELE ? CHAMADO
			else if (tubaroes[3] == false) {
				tubaroes[3] = true;
				tubY[3] = (rand() % 280) - 150;
				while (tubY[3] % 10 != 0) {
					tubY[3] = (rand() % 280) - 150;
				}
				tubY[3] += 13;
			}
			//SE O TUBARAO 4 ESTA FORA ELE ? CHAMADO
			else if (tubaroes[4] == false) {
				tubaroes[4] = true;
				tubY[4] = (rand() % 280) - 150;
				while (tubY[4] % 10 != 0) {
					tubY[4] = (rand() % 280) - 150;
				}
				tubY[4] += 13;
			}
			//SE O TUBARAO 5 ESTA FORA ELE ? CHAMADO
			else if (tubaroes[5] == false) {
				tubaroes[5] = true;
				tubY[5] = (rand() % 280) - 150;
				while (tubY[5] % 10 != 0) {
					tubY[5] = (rand() % 280) - 150;
				}
				tubY[5] += 13;
			}
		}
	}
}
void colocarSubRival() {
	//COLOCA OS SUBMARINOS RIVAIS NA TELA
	randomico = rand() % 40;
	if (randomico == 0) {
		//S? CHAMA SUBMARINO SE TIVER MENOS QUE 6 ATIVOS
		if (qtdsubmarinos < 6) {
			qtdsubmarinos++;
			//SE O SUBMARINO 0 ESTA FORA ELE ? CHAMADO
			if (submarinos[0] == false) {
				submarinos[0] = true;
				//OBTEM UM VALOR PARA O Y DO SUBMARINO DE -140 AT? 140
				srand((unsigned)time(NULL));
				subY[0] = (rand() % 280) - 140;
				tiroSubY[0] = subY[0];
			}
			//SE O SUBMARINO 1 ESTA FORA ELE ? CHAMADO
			else if (submarinos[1] == false) {
				submarinos[1] = true;
				subY[1] = (rand() % 280) - 140;
				tiroSubY[1] = subY[1];
			}
			//SE O SUBMARINO 2 ESTA FORA ELE ? CHAMADO
			else if (submarinos[2] == false) {
				submarinos[2] = true;
				subY[2] = (rand() % 280) - 140;
				tiroSubY[2] = subY[2];
			}
			//SE O SUBMARINO 3 ESTA FORA ELE ? CHAMADO
			else if (submarinos[3] == false) {
				submarinos[3] = true;
				subY[3] = (rand() % 280) - 140;
				tiroSubY[3] = subY[3];
			}
			//SE O SUBMARINO 4 ESTA FORA ELE ? CHAMADO
			else if (submarinos[4] == false) {
				submarinos[4] = true;
				subY[4] = (rand() % 280) - 140;
				tiroSubY[4] = subY[4];
			}
			//SE O SUBMARINO 5 ESTA FORA ELE ? CHAMADO
			else if (submarinos[5] == false) {
				submarinos[5] = true;
				subY[5] = (rand() % 280) - 140;
				tiroSubY[5] = subY[5];
			}
		}
	}
}

void animarMergulhador() {
	//SE O MERGULHADOR 0 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (mergulhador[0] == true) {
		if (merX[0] < 435) {
			merX[0] += 5;
		}
		else {
			merX[0] = -450;
			qtdmergulhadores--;
			mergulhador[0] = false;
		}
	}

	//SE O MERGULHADOR 1 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (mergulhador[1] == true) {
		if (merX[1] > -405) {
			merX[1] -= 5;
		}
		else {
			merX[1] = 450;
			qtdmergulhadores--;
			mergulhador[1] = false;
		}
	}

	//SE O MERGULHADOR 2 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (mergulhador[2] == true) {
		if (merX[2] < 435) {
			merX[2] += 5;
		}
		else {
			merX[2] = -450;
			qtdmergulhadores--;
			mergulhador[2] = false;
		}
	}

	//SE O MERGULHADOR 3 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (mergulhador[3] == true) {
		if (merX[3] > -405) {
			merX[3] -= 5;
		}
		else {
			merX[3] = 450;
			qtdmergulhadores--;
			mergulhador[3] = false;
		}
	}

	//SE O MERGULHADOR 4 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (mergulhador[4] == true) {
		if (merX[4] < 435) {
			merX[4] += 5;
		}
		else {
			merX[4] = -450;
			qtdmergulhadores--;
			mergulhador[4] = false;
		}
	}

	//SE O MERGULHADOR 5 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (mergulhador[5] == true) {
		if (merX[5] > -405) {
			merX[5] -= 5;
		}
		else {
			merX[5] = 450;
			qtdmergulhadores--;
			mergulhador[5] = false;
		}
	}

}
void animarTubaroes() {
	//SE O TUBARAO 0 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (tubaroes[0] == true) {
		if (tubX[0] < 435) {
			tubX[0] += 5;
		}
		else {
			tubX[0] = -450;
			qtdtubaroes--;
			tubaroes[0] = false;
		}
	}
	//SE O TUBARAO 1 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (tubaroes[1] == true) {
		if (tubX[1] > -405) {
			tubX[1] -= 5;
		}
		else {
			tubX[1] = 450;
			qtdtubaroes--;
			tubaroes[1] = false;
		}
	}
	//SE O TUBARAO 2 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (tubaroes[2] == true) {
		if (tubX[2] < 435) {
			tubX[2] += 5;
		}
		else {
			tubX[2] = -450;
			qtdtubaroes--;
			tubaroes[2] = false;
		}
	}
	//SE O TUBARAO 3 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (tubaroes[3] == true) {
		if (tubX[3] > -405) {
			tubX[3] -= 5;
		}
		else {
			tubX[3] = 450;
			qtdtubaroes--;
			tubaroes[3] = false;
		}
	}
	//SE O TUBARAO 4 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (tubaroes[4] == true) {
		if (tubX[4] < 435) {
			tubX[4] += 5;
		}
		else {
			tubX[4] = -450;
			qtdtubaroes--;
			tubaroes[4] = false;
		}
	}
	//SE O TUBARAO 5 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (tubaroes[5] == true) {
		if (tubX[5] > -405) {
			tubX[5] -= 5;
		}
		else {
			tubX[5] = 450;
			qtdtubaroes--;
			tubaroes[5] = false;
		}
	}
}
void animarSubRival() {
	//SE O SUBMARINO 0 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (submarinos[0] == true) {
		if (subX[0] < 435) {
			subX[0] += 5;
			tiroSubX[0] += 5;
		}
		else {
			subX[0] = -450;
			tiroSubX[0] = -450;
			tiroSub[0] = false;
			qtdsubmarinos--;
			submarinos[0] = false;
		}
	}

	//SE O SUBMARINO 1 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (submarinos[1] == true) {
		if (subX[1] > -405) {
			subX[1] -= 5;
			tiroSubX[1] -= 5;
		}
		else {
			subX[1] = 450;
			tiroSubX[1] = 450;
			tiroSub[1] = false;
			qtdsubmarinos--;
			submarinos[1] = false;
		}
	}

	//SE O SUBMARINO 2 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (submarinos[2] == true) {
		if (subX[2] < 435) {
			subX[2] += 5;
			tiroSubX[2] += 5;
		}
		else {
			subX[2] = -450;
			tiroSubX[2] = -450;
			tiroSub[2] = false;
			qtdsubmarinos--;
			submarinos[2] = false;
		}
	}

	//SE O SUBMARINO 3 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (submarinos[3] == true) {
		if (subX[3] > -405) {
			subX[3] -= 5;
			tiroSubX[3] -= 5;
		}
		else {
			subX[3] = 450;
			tiroSubX[3] = 450;
			tiroSub[3] = false;
			qtdsubmarinos--;
			submarinos[3] = false;
		}
	}

	//SE O SUBMARINO 4 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (submarinos[4] == true) {
		if (subX[4] < 435) {
			subX[4] += 5;
			tiroSubX[4] += 5;
		}
		else {
			subX[4] = -450;
			tiroSubX[4] = -450;
			tiroSub[4] = false;
			qtdsubmarinos--;
			submarinos[4] = false;
		}
	}

	//SE O SUBMARINO 5 ESTA ATIVO ELE VAI AT? O FIM E VOLTA AO INICIO
	if (submarinos[5] == true) {
		if (subX[5] > -405) {
			subX[5] -= 5;
			tiroSubX[5] -= 5;
		}
		else {
			subX[5] = 450;
			tiroSubX[5] = 450;
			tiroSub[5] = false;
			qtdsubmarinos--;
			submarinos[5] = false;
		}
	}
}
void animarBarco() {
	if (barco) {
		if (barcoesquerda) {
			barcoX += 5;
			if (barcoX >= 450) {
				barco = false;
				barcoX = 450;
				barcoesquerda = false;
			}
		}
		else {
			barcoX -= 5;
			if (barcoX <= -450) {
				barco = false;
				barcoX = -450;
				barcoesquerda = true;
			}
		}
	}
}

void ativarTiroSubRival() {
	randomico = rand() % 70;
	if (randomico == 0) {
		if (tiroSub[0] == false && submarinos[0] == true) tiroSub[0] = true;
		else if (tiroSub[1] == false && submarinos[1] == true) tiroSub[1] = true;
		else if (tiroSub[2] == false && submarinos[2] == true) tiroSub[2] = true;
		else if (tiroSub[3] == false && submarinos[3] == true) tiroSub[3] = true;
		else if (tiroSub[4] == false && submarinos[4] == true) tiroSub[4] = true;
		else if (tiroSub[5] == false && submarinos[5] == true) tiroSub[5] = true;
	}
}
void executarTiroSubRival() {
	if (tiroSub[0] == true) tiroSubX[0] += 2;
	if (tiroSub[1] == true) tiroSubX[1] -= 2;
	if (tiroSub[2] == true) tiroSubX[2] += 2;
	if (tiroSub[3] == true) tiroSubX[3] -= 2;
	if (tiroSub[4] == true) tiroSubX[4] += 2;
	if (tiroSub[5] == true) tiroSubX[5] -= 2;
}
void executarTiro() {
	//EXECUTA O TIRO SE BASEANDO NO LADO DO SUBMARINO
	if (tiro == true) {
		if (tirodireita == true) {
			tiroX += 30;
			if (tiroX >= 360) {
				tirodireita = false;
				tiro = false;
				tiroY += bufferY;
				bufferY = 0;
				if (esquerda == true) {
					tiroX = posX - 180;
				}
				else {
					tiroX = posX;
				}
			}
		}
		else if (tiroesquerda == true) {
			tiroX -= 30;
			if (tiroX <= -500) {
				tiroesquerda = false;
				tiro = false;
				tiroY += bufferY;
				bufferY = 0;
				if (esquerda == true) {
					tiroX = posX - 180;
				}
				else {
					tiroX = posX;
				}
			}
		}
		else if (esquerda == false) {
			tirodireita = true;
		}
		else if (esquerda == true) {
			tiroesquerda = true;
		}
	}
}

void colisaoSubmarinos() {
	//SE SUBMARINO BATER NO SUBMARINO RIVAL 0
	if (esquerda == true) {
		if (posX - 98 <= subX[0] + 40 && posX > subX[0] - 15 && posY > subY[0] - 20 && posY < subY[0] + 20) {
			//ver que perde vida e tem que limpar toda a tela e reiniciar
			subX[0] = -450;
			submarinos[0] = false;
			qtdsubmarinos--;
			explosaoSubmarino = true;
		}
	}
	else {
		if (posX + 98 >= subX[0] - 10 && posX < subX[0] + 55 && posY > subY[0] - 20 && posY < subY[0] + 20) {
			subX[0] = -450;
			submarinos[0] = false;
			qtdsubmarinos--;
			explosaoSubmarino = true;
		}
	}

	//SE SUBMARINO BATER NO SUBMARINO RIVAL 1
	if (esquerda == true) {
		if (posX - 98 <= subX[1] + 5 && posX > subX[1] - 60 && posY > subY[1] - 20 && posY < subY[1] + 20) {
			subX[1] = 450;
			submarinos[1] = false;
			qtdsubmarinos--;
			explosaoSubmarino = true;
		}
	}
	else {
		if (posX + 98 >= subX[1] - 30 && posX < subX[1] + 15 && posY > subY[1] - 20 && posY < subY[1] + 20) {
			subX[1] = 450;
			submarinos[1] = false;
			qtdsubmarinos--;
			explosaoSubmarino = true;
		}
	}

	//SE SUBMARINO BATER NO SUBMARINO RIVAL 2
	if (esquerda == true) {
		if (posX - 98 <= subX[2] + 40 && posX > subX[2] - 15 && posY > subY[2] - 20 && posY < subY[2] + 20) {
			//ver que perde vida e tem que limpar toda a tela e reiniciar
			subX[2] = -450;
			submarinos[2] = false;
			qtdsubmarinos--;
			explosaoSubmarino = true;
		}
	}
	else {
		if (posX + 98 >= subX[2] - 10 && posX < subX[2] + 55 && posY > subY[2] - 20 && posY < subY[2] + 20) {
			subX[2] = -450;
			submarinos[2] = false;
			qtdsubmarinos--;
			explosaoSubmarino = true;
		}
	}

	//SE SUBMARINO BATER NO SUBMARINO RIVAL 3
	if (esquerda == true) {
		if (posX - 98 <= subX[3] + 5 && posX > subX[3] - 60 && posY > subY[3] - 20 && posY < subY[3] + 20) {
			subX[3] = 450;
			submarinos[3] = false;
			qtdsubmarinos--;
			explosaoSubmarino = true;
		}
	}
	else {
		if (posX + 98 >= subX[3] - 30 && posX < subX[3] + 15 && posY > subY[3] - 20 && posY < subY[3] + 20) {
			subX[3] = 450;
			submarinos[3] = false;
			qtdsubmarinos--;
			explosaoSubmarino = true;
		}
	}

	//SE SUBMARINO BATER NO SUBMARINO RIVAL 4
	if (esquerda == true) {
		if (posX - 98 <= subX[4] + 40 && posX > subX[4] - 15 && posY > subY[4] - 20 && posY < subY[4] + 20) {
			//ver que perde vida e tem que limpar toda a tela e reiniciar
			subX[4] = -450;
			submarinos[4] = false;
			qtdsubmarinos--;
			explosaoSubmarino = true;
		}
	}
	else {
		if (posX + 98 >= subX[4] - 10 && posX < subX[4] + 55 && posY > subY[4] - 20 && posY < subY[4] + 20) {
			subX[4] = -450;
			submarinos[4] = false;
			qtdsubmarinos--;
			explosaoSubmarino = true;
		}
	}

	//SE SUBMARINO BATER NO SUBMARINO RIVAL 5
	if (esquerda == true) {
		if (posX - 98 <= subX[5] + 5 && posX > subX[5] - 60 && posY > subY[5] - 20 && posY < subY[5] + 20) {
			subX[5] = 450;
			submarinos[5] = false;
			qtdsubmarinos--;
			explosaoSubmarino = true;
		}
	}
	else {
		if (posX + 98 >= subX[5] - 30 && posX < subX[5] + 15 && posY > subY[5] - 20 && posY < subY[5] + 20) {
			subX[5] = 450;
			submarinos[5] = false;
			qtdsubmarinos--;
			explosaoSubmarino = true;
		}
	}
}
void colisaoMergulhador() {
	//SE SUBMARINO BATER NO MERGULHADOR 0
	if (esquerda == true) {
		if (posX - 98 <= merX[0] && posX > merX[0] - 15 && posY > merY[0] - 30 && posY < merY[0] + 20) {
			if (mergulhadorescoletados < 8) {
				mergulhadorescoletados++;
			}
			merX[0] = -450;
			mergulhador[0] = false;
			qtdmergulhadores--;
			placar += 10;
		}
	}
	else {
		if (posX + 98 >= merX[0] - 20 && posX < merX[0] - 15 && posY > merY[0] - 30 && posY < merY[0] + 10) {
			if (mergulhadorescoletados < 8) {
				mergulhadorescoletados++;
			}
			merX[0] = -450;
			mergulhador[0] = false;
			qtdmergulhadores--;
			placar += 10;
		}
	}

	//SE SUBMARINO BATER NO MERGULHADOR 1
	if (esquerda == true) {
		if (posX - 98 <= merX[1] + 15 && posX > merX[1] - 15 && posY > merY[1] - 30 && posY < merY[1] + 20) {
			if (mergulhadorescoletados < 8) {
				mergulhadorescoletados++;
			}
			merX[1] = 450;
			mergulhador[1] = false;
			qtdmergulhadores--;
			placar += 10;
		}
	}
	else {
		if (posX + 98 >= merX[1] - 10 && posX < merX[1] - 15 && posY > merY[1] - 30 && posY < merY[1] + 10) {
			if (mergulhadorescoletados < 8) {
				mergulhadorescoletados++;
			}
			merX[1] = 450;
			mergulhador[1] = false;
			qtdmergulhadores--;
			placar += 10;
		}
	}

	//SE SUBMARINO BATER NO MERGULHADOR 2
	if (esquerda == true) {
		if (posX - 98 <= merX[2] && posX > merX[2] - 15 && posY > merY[2] - 30 && posY < merY[2] + 20) {
			if (mergulhadorescoletados < 8) {
				mergulhadorescoletados++;
			}
			merX[2] = -450;
			mergulhador[2] = false;
			qtdmergulhadores--;
			placar += 10;
		}
	}
	else {
		if (posX + 98 >= merX[2] - 20 && posX < merX[2] - 15 && posY > merY[2] - 30 && posY < merY[2] + 10) {
			if (mergulhadorescoletados < 8) {
				mergulhadorescoletados++;
			}
			merX[2] = -450;
			mergulhador[2] = false;
			qtdmergulhadores--;
			placar += 10;
		}
	}

	//SE SUBMARINO BATER NO MERGULHADOR 3
	if (esquerda == true) {
		if (posX - 98 <= merX[3] + 15 && posX > merX[3] - 15 && posY > merY[3] - 30 && posY < merY[3] + 20) {
			if (mergulhadorescoletados < 8) {
				mergulhadorescoletados++;
			}
			merX[3] = 450;
			mergulhador[3] = false;
			qtdmergulhadores--;
			placar += 10;
		}
	}
	else {
		if (posX + 98 >= merX[3] - 10 && posX < merX[3] - 15 && posY > merY[3] - 30 && posY < merY[3] + 10) {
			if (mergulhadorescoletados < 8) {
				mergulhadorescoletados++;
			}
			merX[3] = 450;
			mergulhador[3] = false;
			qtdmergulhadores--;
			placar += 10;
		}
	}

	//SE SUBMARINO BATER NO MERGULHADOR 4
	if (esquerda == true) {
		if (posX - 98 <= merX[4] && posX > merX[4] - 15 && posY > merY[4] - 30 && posY < merY[4] + 20) {
			if (mergulhadorescoletados < 8) {
				mergulhadorescoletados++;
			}
			merX[4] = -450;
			mergulhador[4] = false;
			qtdmergulhadores--;
			placar += 10;
		}
	}
	else {
		if (posX + 98 >= merX[4] - 20 && posX < merX[4] - 15 && posY > merY[4] - 30 && posY < merY[4] + 10) {
			if (mergulhadorescoletados < 8) {
				mergulhadorescoletados++;
			}
			merX[4] = -450;
			mergulhador[4] = false;
			qtdmergulhadores--;
			placar += 10;
		}
	}

	//SE SUBMARINO BATER NO MERGULHADOR 5
	if (esquerda == true) {
		if (posX - 98 <= merX[5] + 15 && posX > merX[5] - 15 && posY > merY[5] - 30 && posY < merY[5] + 20) {
			if (mergulhadorescoletados < 8) {
				mergulhadorescoletados++;
			}
			merX[5] = 450;
			mergulhador[5] = false;
			qtdmergulhadores--;
			placar += 10;
		}
	}
	else {
		if (posX + 98 >= merX[5] - 10 && posX < merX[5] - 15 && posY > merY[5] - 30 && posY < merY[5] + 10) {
			if (mergulhadorescoletados < 8) {
				mergulhadorescoletados++;
			}
			merX[5] = 450;
			mergulhador[5] = false;
			qtdmergulhadores--;
			placar += 10;
		}
	}
}
void colisaoTubarao() {
	//SE SUBMARINO BATER NO TUBARAO 0
	if (esquerda == true) {
		if (posX - 98 <= tubX[0] + 20 && posX > tubX[0] - 40 && posY > tubY[0] - 10 && posY < tubY[0] + 20) {
			tubX[0] = -450;
			tubaroes[0] = false;
			qtdtubaroes--;
			explosaoSubmarino = true;
		}
	}
	else {
		if (posX + 98 >= tubX[0] - 20 && posX < tubX[0] + 35 && posY > tubY[0] - 10 && posY < tubY[0] + 20) {
			tubX[0] = -450;
			tubaroes[0] = false;
			qtdtubaroes--;
			explosaoSubmarino = true;
		}
	}

	//SE SUBMARINO BATER NO TUBARAO 1
	if (esquerda == true) {
		if (posX - 98 <= tubX[1] + 20 && posX > tubX[1] - 40 && posY > tubY[1] - 10 && posY < tubY[1] + 20) {
			tubX[1] = 450;
			tubaroes[1] = false;
			qtdtubaroes--;
			explosaoSubmarino = true;
		}
	}
	else {
		if (posX + 98 >= tubX[1] - 20 && posX < tubX[1] + 35 && posY > tubY[1] - 10 && posY < tubY[1] + 20) {
			tubX[1] = 450;
			tubaroes[1] = false;
			qtdtubaroes--;
			explosaoSubmarino = true;
		}
	}

	//SE SUBMARINO BATER NO TUBARAO 2
	if (esquerda == true) {
		if (posX - 98 <= tubX[2] + 20 && posX > tubX[2] - 40 && posY > tubY[2] - 10 && posY < tubY[2] + 20) {
			tubX[2] = -450;
			tubaroes[2] = false;
			qtdtubaroes--;
			explosaoSubmarino = true;
		}
	}
	else {
		if (posX + 98 >= tubX[2] - 20 && posX < tubX[2] + 35 && posY > tubY[2] - 10 && posY < tubY[2] + 20) {
			tubX[2] = -450;
			tubaroes[2] = false;
			qtdtubaroes--;
			explosaoSubmarino = true;
		}
	}

	//SE SUBMARINO BATER NO TUBARAO 3
	if (esquerda == true) {
		if (posX - 98 <= tubX[3] + 20 && posX > tubX[3] - 40 && posY > tubY[3] - 10 && posY < tubY[3] + 20) {
			tubX[3] = 450;
			tubaroes[3] = false;
			qtdtubaroes--;
			explosaoSubmarino = true;
		}
	}
	else {
		if (posX + 98 >= tubX[3] - 20 && posX < tubX[3] + 35 && posY > tubY[3] - 10 && posY < tubY[3] + 20) {
			tubX[3] = 450;
			tubaroes[3] = false;
			qtdtubaroes--;
			explosaoSubmarino = true;
		}
	}

	//SE SUBMARINO BATER NO TUBARAO 4
	if (esquerda == true) {
		if (posX - 98 <= tubX[4] + 20 && posX > tubX[4] - 40 && posY > tubY[4] - 10 && posY < tubY[4] + 20) {
			tubX[4] = -450;
			tubaroes[4] = false;
			qtdtubaroes--;
			explosaoSubmarino = true;
		}
	}
	else {
		if (posX + 98 >= tubX[4] - 20 && posX < tubX[4] + 35 && posY > tubY[4] - 10 && posY < tubY[4] + 20) {
			tubX[4] = -450;
			tubaroes[4] = false;
			qtdtubaroes--;
			explosaoSubmarino = true;
		}
	}

	//SE SUBMARINO BATER NO TUBARAO 5
	if (esquerda == true) {
		if (posX - 98 <= tubX[5] + 20 && posX > tubX[5] - 40 && posY > tubY[5] - 10 && posY < tubY[5] + 20) {
			tubX[5] = 450;
			tubaroes[5] = false;
			qtdtubaroes--;
			explosaoSubmarino = true;
		}
	}
	else {
		if (posX + 98 >= tubX[5] - 20 && posX < tubX[5] + 35 && posY > tubY[5] - 10 && posY < tubY[5] + 20) {
			tubX[5] = 450;
			tubaroes[5] = false;
			qtdtubaroes--;
			explosaoSubmarino = true;
		}
	}
}
void colisaoBarco() {
	if (esquerda) {
		if (posX + 98 >= barcoX + 70 && posX < barcoX + 150 && posY > 130) {
			barcoesquerda = true;
			barcoX = -450;
			barco = false;
			explosaoSubmarino = true;
		}
	}
	else {
		if (posX + 98 >= barcoX - 10 && posX < barcoX + 55 && posY > 130) {
			barcoesquerda = true;
			barcoX = -450;
			barco = false;
			explosaoSubmarino = true;
		}
	}
}
void colisaoTiroTubarao() {
	if (tiro == true) {
		//SE O TIRO ACERTAR O TUBARAO 0
		if (tiroX + 80 <= tubX[0] + 25 && tiroX + 80 >= tubX[0] - 30 && tiroY + 5 >= tubY[0] + 5 && tiroY + 5 <= tubY[0] + 15) {
			qtdtubaroes--;
			tubX[0] = -450;
			placar += 20;
			tubaroes[0] = false;
			tiro = false;
			tiroY += bufferY;
			bufferY = 0;
			if (esquerda == true) {
				tiroX = posX - 180;
			}
			else {
				tiroX = posX;
			}
			tiroesquerda = false;
			tirodireita = false;
		}

		//SE O TIRO ACERTAR O TUBARAO 1
		if (tiroX + 80 <= tubX[1] + 15 && tiroX + 80 >= tubX[1] - 30 && tiroY + 5 >= tubY[1] + 5 && tiroY + 5 <= tubY[1] + 15) {
			qtdtubaroes--;
			tubX[1] = 450;
			placar += 20;
			tubaroes[1] = false;
			tiro = false;
			tiroY += bufferY;
			bufferY = 0;
			if (esquerda == true) {
				tiroX = posX - 180;
			}
			else {
				tiroX = posX;
			}
			tiroesquerda = false;
			tirodireita = false;
		}

		//SE O TIRO ACERTAR O TUBARAO 2
		if (tiroX + 80 <= tubX[2] + 25 && tiroX + 80 >= tubX[2] - 30 && tiroY + 5 >= tubY[2] + 5 && tiroY + 5 <= tubY[2] + 15) {
			qtdtubaroes--;
			tubX[2] = -450;
			placar += 20;
			tubaroes[2] = false;
			tiro = false;
			tiroY += bufferY;
			bufferY = 0;
			if (esquerda == true) {
				tiroX = posX - 180;
			}
			else {
				tiroX = posX;
			}
			tiroesquerda = false;
			tirodireita = false;
		}

		//SE O TIRO ACERTAR O TUBARAO 3
		if (tiroX + 80 <= tubX[3] + 15 && tiroX + 80 >= tubX[3] - 30 && tiroY + 5 >= tubY[3] + 5 && tiroY + 5 <= tubY[3] + 15) {
			qtdtubaroes--;
			tubX[3] = 450;
			placar += 20;
			tubaroes[3] = false;
			tiro = false;
			tiroY += bufferY;
			bufferY = 0;
			if (esquerda == true) {
				tiroX = posX - 180;
			}
			else {
				tiroX = posX;
			}
			tiroesquerda = false;
			tirodireita = false;
		}

		//SE O TIRO ACERTAR O TUBARAO 4
		if (tiroX + 80 <= tubX[4] + 25 && tiroX + 80 >= tubX[4] - 30 && tiroY + 5 >= tubY[4] + 5 && tiroY + 5 <= tubY[4] + 15) {
			qtdtubaroes--;
			tubX[4] = -450;
			placar += 20;
			tubaroes[4] = false;
			tiro = false;
			tiroY += bufferY;
			bufferY = 0;
			if (esquerda == true) {
				tiroX = posX - 180;
			}
			else {
				tiroX = posX;
			}
			tiroesquerda = false;
			tirodireita = false;
		}

		//SE O TIRO ACERTAR O TUBARAO 5
		if (tiroX + 80 <= tubX[5] + 15 && tiroX + 80 >= tubX[5] - 30 && tiroY + 5 >= tubY[5] + 5 && tiroY + 5 <= tubY[5] + 15) {
			qtdtubaroes--;
			tubX[5] = 450;
			placar += 20;
			tubaroes[5] = false;
			tiro = false;
			tiroY += bufferY;
			bufferY = 0;
			if (esquerda == true) {
				tiroX = posX - 180;
			}
			else {
				tiroX = posX;
			}
			tiroesquerda = false;
			tirodireita = false;
		}
	}
}
void colisaoTiroSubRival() {
	if (tiro == true) {
		//SE O TIRO ACERTAR O SUBMARINO RIVAL 0
		if (tiroX + 80 <= subX[0] + 40 && tiroX + 80 >= subX[0] - 10 && tiroY + 5 <= subY[0] + 10 && tiroY + 5 >= subY[0] - 10) {
			qtdsubmarinos--;
			subX[0] = -450;
			tiroSubX[0] = -450;
			tiroSub[0] = false;
			placar += 30;
			submarinos[0] = false;
			tiro = false;
			tiroY += bufferY;
			bufferY = 0;
			if (esquerda == true) {
				tiroX = posX - 180;
			}
			else {
				tiroX = posX;
			}
			tiroesquerda = false;
			tirodireita = false;
		}

		//SE O TIRO ACERTAR O SUBMARINO RIVAL 1
		if (tiroX + 80 <= subX[1] && tiroX + 80 >= subX[1] - 50 && tiroY + 5 <= subY[1] + 10 && tiroY + 5 >= subY[1] - 10) {
			qtdsubmarinos--;
			subX[1] = 450;
			tiroSubX[1] = 450;
			tiroSub[1] = false;
			placar += 30;
			submarinos[1] = false;
			tiro = false;
			tiroY += bufferY;
			bufferY = 0;
			if (esquerda == true) {
				tiroX = posX - 180;
			}
			else {
				tiroX = posX;
			}
			tiroesquerda = false;
			tirodireita = false;
		}

		//SE O TIRO ACERTAR O SUBMARINO RIVAL 2
		if (tiroX + 80 <= subX[2] + 40 && tiroX + 80 >= subX[2] - 10 && tiroY + 5 <= subY[2] + 10 && tiroY + 5 >= subY[2] - 10) {
			qtdsubmarinos--;
			subX[2] = -450;
			tiroSubX[2] = -450;
			tiroSub[2] = false;
			placar += 30;
			submarinos[2] = false;
			tiro = false;
			tiroY += bufferY;
			bufferY = 0;
			if (esquerda == true) {
				tiroX = posX - 180;
			}
			else {
				tiroX = posX;
			}
			tiroesquerda = false;
			tirodireita = false;
		}

		//SE O TIRO ACERTAR O SUBMARINO RIVAL 3
		if (tiroX + 80 <= subX[3] && tiroX + 80 >= subX[3] - 50 && tiroY + 5 <= subY[3] + 10 && tiroY + 5 >= subY[3] - 10) {
			qtdsubmarinos--;
			subX[3] = 450;
			tiroSubX[3] = 450;
			tiroSub[3] = false;
			placar += 30;
			submarinos[3] = false;
			tiro = false;
			tiroY += bufferY;
			bufferY = 0;
			if (esquerda == true) {
				tiroX = posX - 180;
			}
			else {
				tiroX = posX;
			}
			tiroesquerda = false;
			tirodireita = false;

		}

		//SE O TIRO ACERTAR O SUBMARINO RIVAL 4
		if (tiroX + 80 <= subX[4] + 40 && tiroX + 80 >= subX[4] - 10 && tiroY + 5 <= subY[4] + 10 && tiroY + 5 >= subY[4] - 10) {
			qtdsubmarinos--;
			subX[4] = -450;
			tiroSubX[4] = -450;
			tiroSub[4] = false;
			placar += 30;
			submarinos[4] = false;
			tiro = false;
			tiroY += bufferY;
			bufferY = 0;
			if (esquerda == true) {
				tiroX = posX - 180;
			}
			else {
				tiroX = posX;
			}
			tiroesquerda = false;
			tirodireita = false;
		}

		//SE O TIRO ACERTAR O SUBMARINO RIVAL 5
		if (tiroX + 80 <= subX[5] && tiroX + 80 >= subX[5] - 50 && tiroY + 5 <= subY[5] + 10 && tiroY + 5 >= subY[5] - 10) {
			qtdsubmarinos--;
			subX[5] = 450;
			tiroSubX[5] = 450;
			tiroSub[5] = false;
			placar += 30;
			submarinos[5] = false;
			tiro = false;
			tiroY += bufferY;
			bufferY = 0;
			if (esquerda == true) {
				tiroX = posX - 180;
			}
			else {
				tiroX = posX;
			}
			tiroesquerda = false;
			tirodireita = false;
		}
	}
}
void colisaoTiroSubRivalnoSub() {
	//SE O TIRO SO SUBMARINO RIVAL 0 EST? ATIVO  E COLIDE COM O SUBMARINO
	if (tiroSub[0] == true) {
		if (esquerda == false && posX - 60 < tiroSubX[0] && posX + 70 > tiroSubX[0] && posY + 10 > tiroSubY[0] && posY < tiroSubY[0] + 10) {
			explosaoSubmarino = true;
		}
		else if (esquerda == true && posX - 140 < tiroSubX[0] && posX - 10 > tiroSubX[0] && posY + 10 > tiroSubY[0] && posY < tiroSubY[0] + 10) {
			explosaoSubmarino = true;
		}
	}

	//SE O TIRO SO SUBMARINO RIVAL 1 EST? ATIVO  E COLIDE COM O SUBMARINO
	if (tiroSub[1] == true) {
		if (esquerda == false && posX - 60 < tiroSubX[1] && posX + 70 > tiroSubX[1] && posY + 10 > tiroSubY[1] && posY < tiroSubY[1] + 10) {
			explosaoSubmarino = true;
		}
		else if (esquerda == true && posX - 140 < tiroSubX[1] && posX - 10 > tiroSubX[1] && posY + 10 > tiroSubY[1] && posY < tiroSubY[1] + 10) {
			explosaoSubmarino = true;
		}
	}

	//SE O TIRO SO SUBMARINO RIVAL 2 EST? ATIVO  E COLIDE COM O SUBMARINO
	if (tiroSub[2] == true) {
		if (esquerda == false && posX - 60 < tiroSubX[2] && posX + 70 > tiroSubX[2] && posY + 10 > tiroSubY[2] && posY < tiroSubY[2] + 10) {
			explosaoSubmarino = true;
		}
		else if (esquerda == true && posX - 140 < tiroSubX[2] && posX - 10 > tiroSubX[2] && posY + 10 > tiroSubY[2] && posY < tiroSubY[2] + 10) {
			explosaoSubmarino = true;
		}
	}

	//SE O TIRO SO SUBMARINO RIVAL 3 EST? ATIVO  E COLIDE COM O SUBMARINO
	if (tiroSub[3] == true) {
		if (esquerda == false && posX - 60 < tiroSubX[3] && posX + 70 > tiroSubX[3] && posY + 10 > tiroSubY[3] && posY < tiroSubY[3] + 10) {
			explosaoSubmarino = true;
		}
		else if (esquerda == true && posX - 140 < tiroSubX[3] && posX - 10 > tiroSubX[3] && posY + 10 > tiroSubY[3] && posY < tiroSubY[3] + 10) {
			explosaoSubmarino = true;
		}
	}

	//SE O TIRO SO SUBMARINO RIVAL 4 EST? ATIVO  E COLIDE COM O SUBMARINO
	if (tiroSub[4] == true) {
		if (esquerda == false && posX - 60 < tiroSubX[4] && posX + 70 > tiroSubX[4] && posY + 10 > tiroSubY[4] && posY < tiroSubY[4] + 10) {
			explosaoSubmarino = true;
		}
		else if (esquerda == true && posX - 140 < tiroSubX[4] && posX - 10 > tiroSubX[4] && posY + 10 > tiroSubY[4] && posY < tiroSubY[4] + 10) {
			explosaoSubmarino = true;
		}
	}

	//SE O TIRO SO SUBMARINO RIVAL 5 EST? ATIVO  E COLIDE COM O SUBMARINO
	if (tiroSub[5] == true) {
		if (esquerda == false && posX - 60 < tiroSubX[5] && posX + 70 > tiroSubX[5] && posY + 10 > tiroSubY[5] && posY < tiroSubY[5] + 10) {
			explosaoSubmarino = true;
		}
		else if (esquerda == true && posX - 140 < tiroSubX[5] && posX - 10 > tiroSubX[5] && posY + 10 > tiroSubY[5] && posY < tiroSubY[5] + 10) {
			explosaoSubmarino = true;
		}
	}
}

void Perdeu() {
	//SE PERDER UMA VIDA
	if (perdeu == true) {
		perdeu = false;
		vidas--;
		contador = 0;
		contador1 = 0;
		contador2 = 0;

		if (mergulhadorescoletados >= 2)	mergulhadorescoletados -= 2;
		else if (mergulhadorescoletados == 1)	mergulhadorescoletados--;
		for (int i = 0; i < 6; i++) {
			mergulhador[i] = false;
			tubaroes[i] = false;
			submarinos[i] = false;
			tiroSub[i] = false;
			if (i % 2 == 0) {
				subX[i] = -450;
				merX[i] = -450;
				tubX[i] = -450;
				tiroSubX[i] = -450;
			}
			else {
				subX[i] = 450;
				merX[i] = 450;
				tubX[i] = 450;
				tiroSubX[i] = 450;
			}
		}
		barcoesquerda = true;
		barcoX = -450;
		barco = true;
		qtdtubaroes = 0;
		qtdsubmarinos = 0;
		qtdmergulhadores = 0;
		barraoxigenio = 0;

		if (vidas == 0) morreu = true;
	}
}
void Morreu() {
	if (morreu == true) {
		if (placar > pontuacaomaxima) pontuacaomaxima = placar;
		rodando = false;
		glBegin(GL_QUADS);
		glColor3f(0, 0, 0);
		glVertex2f(-150, 100);
		glVertex2f(150, 100);
		glVertex2f(150, -100);
		glVertex2f(-150, -100);
		glEnd();
		glColor3f(1, 0, 0);
		DesenhaTexto("GAME OVER", -70, 0, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

void desenhar() {
	if (menu == true) {
		if (opcaoSelecionada == 0) {
			switch (opcaomenu) {
			case 1:
				DesenhaIcone(47);
				break;
			case 2:
				DesenhaIcone(6);
				break;
			case 3:
				DesenhaIcone(-35);
				break;
			default:
				printf("W.O.");
				break;
			}
		}


		glColor3f(1, 1, 1); 
		char string[50];
		sprintf(string, "Pontuacao maxima: %d", pontuacaomaxima);
		DesenhaTexto(string, -390, 230, GLUT_BITMAP_8_BY_13);
		DesenhaTexto("SEA SUB", -30, 180, GLUT_BITMAP_TIMES_ROMAN_24);
		if (opcaoSelecionada == 0) {
			DesenhaTexto("- Use as setas para mover - ", -50, 110, GLUT_BITMAP_HELVETICA_12);
			if (animaMenu == true) DesenhaTexto("- Tecle 0 para selecionar - ", -48, 80, GLUT_BITMAP_HELVETICA_12);
			DesenhaTexto("- Iniciar jogo", -40, 40, GLUT_BITMAP_HELVETICA_18);
			DesenhaTexto("- Regras do jogo", -40, 0, GLUT_BITMAP_HELVETICA_18);
			DesenhaTexto("- Controles", -40, -40, GLUT_BITMAP_HELVETICA_18);
		}
		if (opcaoSelecionada == 2) {
			if (animaMenu == true) DesenhaTexto("- Tecle 0 para voltar - ", -48, 80, GLUT_BITMAP_HELVETICA_12);
			glPushMatrix();
			glTranslatef(-50, 0, 0);
			DesenhaSubRival(-130, 30, -500, 0);
			glColor3f(1, 1, 1);
			DesenhaTexto(" - 30 Pontos ao destruir. - Colidindo morre.", -80, 25, GLUT_BITMAP_8_BY_13);

			DesenhaMergulhador(-110, -10);
			glColor3f(1, 1, 1);
			DesenhaTexto(" - 10 Pontos ao coletar. - Colidindo coleta.", -80, -20, GLUT_BITMAP_8_BY_13);

			DesenhaTubarao(-120, -70);
			glColor3f(1, 1, 1);
			DesenhaTexto(" - 20 Pontos ao destruir. - Colidindo morre.", -80, -65, GLUT_BITMAP_8_BY_13);

			glPushMatrix();
			glTranslatef(0, -270, 0);
			DesenhaBarco(-140);
			glPopMatrix();
			glColor3f(1, 1, 1);
			DesenhaTexto(" - Colidindo morre.", -80, -110, GLUT_BITMAP_8_BY_13);
			glPopMatrix();
		}
		if (opcaoSelecionada == 3) {
			if (animaMenu == true) DesenhaTexto("- Tecle 0 para voltar - ", -48, 80, GLUT_BITMAP_HELVETICA_12);
			DesenhaTexto("0", -80, 30, GLUT_BITMAP_TIMES_ROMAN_24);
			DesenhaTexto(" - Atira", -40, 34, GLUT_BITMAP_9_BY_15);

			DesenhaTexto("W", -80, 0, GLUT_BITMAP_TIMES_ROMAN_24);
			DesenhaTexto(" - Acima", -40, 4, GLUT_BITMAP_9_BY_15);

			DesenhaTexto("A", -80, -30, GLUT_BITMAP_TIMES_ROMAN_24);
			DesenhaTexto(" - Esquerda", -40, -26, GLUT_BITMAP_9_BY_15);

			DesenhaTexto("S", -80, -60, GLUT_BITMAP_TIMES_ROMAN_24);
			DesenhaTexto(" - Abaixo", -40, -56, GLUT_BITMAP_9_BY_15);

			DesenhaTexto("D", -80, -90, GLUT_BITMAP_TIMES_ROMAN_24);
			DesenhaTexto(" - Direita", -40, -86, GLUT_BITMAP_9_BY_15);

			DesenhaTexto("P", -80, -120, GLUT_BITMAP_TIMES_ROMAN_24);
			DesenhaTexto(" - Pause", -40, -118, GLUT_BITMAP_9_BY_15);

			DesenhaTexto("8", -80, -150, GLUT_BITMAP_TIMES_ROMAN_24);
			DesenhaTexto(" - Aumenta Velocidade", -40, -148, GLUT_BITMAP_9_BY_15);

			DesenhaTexto("2", -80, -180, GLUT_BITMAP_TIMES_ROMAN_24);
			DesenhaTexto(" - Diminui Velocidade", -40, -178, GLUT_BITMAP_9_BY_15);
		}

		DesenhaTexto("FELIPE PERGHER", -380, -240, GLUT_BITMAP_9_BY_15);
		DesenhaTexto("IFC VIDEIRA", 280, -240, GLUT_BITMAP_9_BY_15);
	}
	else {
		DesenhaFundo();
		DesenhaBala();
		DesenhaSubmarino();
		DesenhaBarco(barcoX);
		if (explosaoSubmarino == true) DesenhaExplosao();

		//-----------------------------------------------------------------

		//DESENHA OS MINI SUBMARINOS AO LADO DA PONTUACAO MOSTRANDO AS VIDAS
		if (vidas >= 1) DesenhaMiniSubmarino(-180, 225);
		if (vidas >= 2) DesenhaMiniSubmarino(-110, 225);
		if (vidas >= 3) DesenhaMiniSubmarino(-40, 225);

		//-----------------------------------------------------------------

		//DESENHA OS MERGULHADORES, TEM 6 MERGULHADORES
		if (mergulhador[0] == true) DesenhaMergulhador(merX[0], merY[0]);
		if (mergulhador[1] == true) DesenhaMergulhadorD(merX[1], merY[1]);
		if (mergulhador[2] == true) DesenhaMergulhador(merX[2], merY[2]);
		if (mergulhador[3] == true) DesenhaMergulhadorD(merX[3], merY[3]);
		if (mergulhador[4] == true) DesenhaMergulhador(merX[4], merY[4]);
		if (mergulhador[5] == true) DesenhaMergulhadorD(merX[5], merY[5]);

		//-----------------------------------------------------------------

		//DESENHA OS MERGULHADORES COLETADOS AO LADO DO OXIGENIO
		if (mergulhadorescoletados >= 1) DesenhaMergulhador(80, -188);
		if (mergulhadorescoletados >= 2) DesenhaMergulhador(120, -188);
		if (mergulhadorescoletados >= 3) DesenhaMergulhador(160, -188);
		if (mergulhadorescoletados >= 4) DesenhaMergulhador(200, -188);
		if (mergulhadorescoletados >= 5) DesenhaMergulhador(240, -188);
		if (mergulhadorescoletados >= 6) DesenhaMergulhador(280, -188);
		if (mergulhadorescoletados >= 7) DesenhaMergulhador(320, -188);
		if (mergulhadorescoletados >= 8) DesenhaMergulhador(360, -188);

		//-----------------------------------------------------------------

		//DESENHA OS TUBAR?ES, TEM 6 TUBAR?ES
		if (tubaroes[0] == true) DesenhaTubarao(tubX[0], tubY[0]);
		if (tubaroes[1] == true) DesenhaTubaraoD(tubX[1], tubY[1]);
		if (tubaroes[2] == true) DesenhaTubarao(tubX[2], tubY[2]);
		if (tubaroes[3] == true) DesenhaTubaraoD(tubX[3], tubY[3]);
		if (tubaroes[4] == true) DesenhaTubarao(tubX[4], tubY[4]);
		if (tubaroes[5] == true) DesenhaTubaraoD(tubX[5], tubY[5]);

		//-----------------------------------------------------------------

		//DESENHA OS SUBMARINOS RIVAIS, TEM 6 SUBMARINOS RIVAIS
		if (submarinos[0] == true) DesenhaSubRival(subX[0], subY[0], tiroSubX[0], tiroSubY[0]);
		if (submarinos[1] == true) DesenhaSubRivalD(subX[1], subY[1], tiroSubX[1], tiroSubY[1]);
		if (submarinos[2] == true) DesenhaSubRival(subX[2], subY[2], tiroSubX[2], tiroSubY[2]);
		if (submarinos[3] == true) DesenhaSubRivalD(subX[3], subY[3], tiroSubX[3], tiroSubY[3]);
		if (submarinos[4] == true) DesenhaSubRival(subX[4], subY[4], tiroSubX[4], tiroSubY[4]);
		if (submarinos[5] == true) DesenhaSubRivalD(subX[5], subY[5], tiroSubX[5], tiroSubY[5]);

		//SE PERDER UMA VIDA
		glColor3f(0, 0, 0);
		if (pausado == false && rodando == false && bonusMergulhador == false && oxigenio == false && morreu == false && explosaoSubmarino == false) {
			DesenhaTexto("Tecle 0 para Continuar!", -100, 0, GLUT_BITMAP_TIMES_ROMAN_24);
			DesenhaTexto("Tecle 9 para sair!", -70, -50, GLUT_BITMAP_9_BY_15);
		}
		//SE PAUSAR
		glColor3f(0, 0, 0);
		if (pausado && rodando == false) {
			DesenhaTexto("PAUSE", -20, 20, GLUT_BITMAP_TIMES_ROMAN_24);
			DesenhaTexto("Tecle P para Continuar!", -100, 0, GLUT_BITMAP_TIMES_ROMAN_24);
			DesenhaTexto("Tecle 9 para sair!", -70, -50, GLUT_BITMAP_9_BY_15);
		}
		//SE PERDER UMA VIDA
		Perdeu();
		//SE ACABAR AS VIDAS
		Morreu();
	}
}
void animacao(int valor) {
	if (menu == true) {
		contador1++;
		if (contador1 % 5 == 0) {
			if (animaMenu == false) animaMenu = true;
			else animaMenu = false;
		}

	}
	else {
		//SE O JOGO EST? ATIVO
		if (rodando) {
			animarOxigenio();
			animarHelice();
			executarTiro();

			ativarTiroSubRival();
			executarTiroSubRival();

			colocarMegulhadores();
			colocarTubaroes();
			colocarSubRival();

			animarMergulhador();
			animarTubaroes();
			animarSubRival();
			animarBarco();

			colisaoMergulhador();
			colisaoSubmarinos();
			colisaoTubarao();
			colisaoBarco();

			colisaoTiroTubarao();
			colisaoTiroSubRival();

			colisaoTiroSubRivalnoSub();
		}
		//SE O CARA SUBIR COM OS 8 MERGULHADORES
		if (bonusMergulhador == true) {
			Sleep(300);
			placar += 50;
			mergulhadorescoletados--;
			if (mergulhadorescoletados == 0) {
				bonusMergulhador = false;
				oxigenio = true;
			}
		}
		if (oxigenio) {
			barrafinal = false;
			if (vidas < 3) vidas++;
			if (barraoxigenio < 0) {
				barraoxigenio += 5;
				if (barraoxigenio >= 0) {
					barraoxigenio = 0;
					oxigenio = false;
					rodando = true;
				}
			}
		}
		//QUANDO O CARA MORRE
		if (explosaoSubmarino == true) {
			rodando = false;
			if (cor == false) cor = true;
			else cor = false;
			contador2++;

			if (contador2 == 20) {
				perdeu = true;
				explosaoSubmarino = false;
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(velocidade, animacao, 1);
}
void keyboard(unsigned char tecla, int x, int y) {
	if (pausado == false) {
		if (tecla == 'w' || tecla == 'W') {
			if (posY != 160) {
				posY += 10;
				if (tiro == false) {
					tiroY += 10;
				}
				else {
					bufferY += 10;
				}
			}
		}
		if (tecla == 's' || tecla == 'S') {
			if (posY != -140) {
				posY -= 10;
				if (tiro == false) {
					tiroY -= 10;
				}
				else {
					bufferY -= 10;
				}
			}
		}
		if (tecla == 'a' || tecla == 'A') {
			if (posX != -300) {
				posX -= 20;
				if (tiro == false) {
					tiroX -= 20;
				}
			}
			if (esquerda == false) {
				esquerda = true;
				posX += 100;
				if (tiro == false) tiroX -= 80;
			}

		}
		if (tecla == 'd' || tecla == 'D') {
			if (posX != 300) {
				posX += 20;
				if (tiro == false) {
					tiroX += 20;
				}
			}
			if (esquerda == true) {
				esquerda = false;
				posX -= 100;
				if (tiro == false) tiroX += 80;
			}
		}
	}

	if (tecla == '0') {
		if (morreu == true) {
			menu = true;
			morreu = false;
			opcaoSelecionada = 0;
			return;
		}
		if (menu == true) {
			if (opcaomenu == 1 && opcaoSelecionada == 0) {
				opcaoSelecionada = 1;
				menu = false;
				vidas = 3;
				rodando = true;
				placar = 0;
				posX = 0;
				posY = 0;
				tiroX = 0;
				tiroY = 0;
				esquerda = false;
				return;
			}
			if (opcaoSelecionada == 3 || opcaoSelecionada == 2) {
				opcaoSelecionada = 0;
				opcaomenu = 1;
			}
			if (opcaomenu == 2) opcaoSelecionada = 2;
			if (opcaomenu == 3) opcaoSelecionada = 3;
			return;
		}
		if (rodando == false && pausado == false) {
			rodando = true;
			return;
		}
		if (tiro == false) tiro = true;
	}
	if (tecla == '9') {
		if (pausado || rodando == false && pausado == false) {
			menu = true;
			pausado = false;
			opcaoSelecionada = 0;
			opcaomenu = 1;
		}
	}
	if (tecla == 'p' || tecla == 'P') {
		if (pausado) {
			pausado = false;
			rodando = true;
		}
		else {
			pausado = true;
			rodando = false;
		}
	}
	if (tecla == '8') {
		if (velocidade >= 20) velocidade -= 10;
	}
	if (tecla == '2') {
		if (velocidade <= 150) velocidade += 10;
	}
	glutPostRedisplay();
}
void SpecialInput(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		if (opcaomenu > 1 && opcaoSelecionada == 0) opcaomenu--;
	}
	if (key == GLUT_KEY_DOWN) {
		if (opcaomenu < 3 && opcaoSelecionada == 0) opcaomenu++;
	}
	glutPostRedisplay();
}
void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (menu == true) glClearColor(0, 0, 0, 1);
	else glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(janela_largura / 2, janela_altura / 2, 0);
	glViewport(0, 0, janela_largura, janela_altura);
	desenhar();
	glutSwapBuffers();
}
void tela(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, janela_largura, 0, janela_altura);
	glMatrixMode(GL_MODELVIEW);
}