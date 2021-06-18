
#include "ST7735.h"
#include "font5x7.h"
#include "font6x9.h"
#include "hagl.h"
#include "hsl.h"
/*zmienne z innych części programu */

/* z silnika : */

#define current_angle		// aktualne położenie silnika
#define predicted_angle		// docelowe położenie silnika
int tryb;
double start_angle;
double rot_angle;		//kat startowy silnika

#define BLACK     0x0000
#define RED       0xf800
#define GREEN     0x07e0
#define BLUE      0x001f
#define YELLOW    0xffe0
#define MAGENTA   0xf81f
#define CYAN      0x07ff
#define WHITE     0xffff

uint16_t gesture;
uint16_t gesture_2;
uint16_t gesture_rot_direction;
#define Xi
#define Yi
#define Zi
/* deklaracje wszystkich funkcji żeby sie nie wywalało od czapy */
void Screen_Motor_Steering( uint16_t gesture_2);
void GoTo_0_mode ( uint16_t gesture);
void GoTo_1_mode(uint16_t gesture);
void potentiometer_animation(int gesture_rot_direction, uint16_t Screen_Height, uint16_t Screen_Width);
void Angle_menu ( wchar_t *Title, uint16_t current_angle, wchar_t *Mode );
void Current_angle_screen(int current_angle);
void Screen_Angular_Velocity(int angular_velocity);
void Euler_Angular_Reading_Panel(int Xi, int Yi, int Zi);
/* Ekran startowy */
void Start_Screen (uint16_t gesture)
{
	hagl_fill_rectangle(1,1,50,30, YELLOW);
	hagl_fill_rectangle(1,129,50,159, YELLOW);
	hagl_fill_rectangle(77,1,77+50,30+1, YELLOW);
	hagl_fill_rectangle(77,129,77+50,129+30, YELLOW);
	hagl_put_text(u"Ster silnikiem",2,2, BLACK, font5x7);
	hagl_put_text(u"predkosc katowa",2,130, BLACK, font5x7);
	hagl_put_text(u"Info",78,2, BLACK, font5x7);
	hagl_put_text(u"Euler",78,130, BLACK, font5x7);

	switch (gesture)
	{
	case 1:
	hagl_fill_rectangle(1,1,50,30, CYAN);
	hagl_putPtext(u"Ster silnikiem",2,2, RED, font5x7);
	
	Screen_Motor_Steering(gesture_2);
	break;
	
	case 2:
	hagl_fill_rectangle(1,129,50,159, CYAN);
	hagl_putPtext(u"predkosc katowa",2,130, RED, font5x7);
	break;
	
	case 3:
	hagl_fill_rectangle(77,1,77+50,30+1, CYAN);
	hagl_putPtext(u"Info",78,2, RED, font5x7);
	break;
	
	case 4:
	hagl_fill_rectangle(77,129,77+50,30+129, CYAN);
	hagl_put_text(u"Euler",78,130, RED, font5x7);
	Euler_Angular_Reading_Panel (Xi, Yi, Zi);
	break;
	}
}


/* Menu wyboru trybu sterowania silnikiem */
void Screen_Motor_Steering( uint16_t gesture_2)
{
	int pos_x0 = 29;
	int width = 70;
	int height = 15;
	
	hagl_fill_rounded_rectangle(pos_x0,140,pos_x0 + width, 140 + height, 3, YELLOW);
	hagl_put_text("TRYB 0", pos_x0 + 5, 145, RED, font6x9);
	hagl_fill_rounded_rectangle( pos_x0, 120, pos_x0 + width, 120 + height, 3, YELLOW );
	hagl_put_text("TRYB 1", pos_x0 + 5, 125, RED, font6x9);
	
	hagl_put_text("Opis trybu 0", 5, 100, BLACK, font5x7);
	hagl_put_text("Opis trybu 1", 5, 50, BLACK, font5x7);
	
	switch(gesture_2)
	{
		case 1:
		hagl_fill_rounded_rectangle(pos_x0,140,pos_x0 + width, 140 + height, 3, CYAN);
		hagl_put_text("TRYB 0", pos_x0 + 5, 145, RED, font6x9);
		tryb == 0;
		GoTo_0_mode(gesture);
		break;
		
		case 2:
		hagl_fill_rounded_rectangle( pos_x0, 120, pos_x0 + width, 120 + height, 3, CYAN);
		hagl_put_text("TRYB 1", pos_x0 + 5, 125, RED, font6x9);
		tryb == 1;
		GoTo_1_mode(gesture);

		break;
	}
}


/*kąty wybierane za pomocą gestu obracania palcem */
/* panel trybu 0 pracy silnika - poruszanie sie z kierunku a na kierunek B */
void GoTo_0_mode ( uint16_t gesture)
{
	/* Menu trybu 0 */
	hagl_fill_rectangle(1,1,50,30, CYAN);
	hagl_putPtext(u"Tryb 0",2,2, BLACK, font6x9);

	hagl_fill_rectangle(1,129,50,159, YELLOW);
	hagl_fill_rectangle(77,1,77+50,30+1, YELLOW);
	hagl_fill_rectangle(77,129,77+50,129+30, YELLOW);
	hagl_fill_rectangle(80-24.5,74-15+10,80+24.5,74+15+10, YELLOW);
	hagl_fill_rectangle(80-24.5,74-15-10,80+24.5,74+15-10, YELLOW);
	//10 odstep miedzy prostokatami na srodku

	hagl_put_text(u"Kat startowy",2,130, BLACK, font5x7);
	hagl_put_text(u"Powrot",78,2, BLACK, font5x7);
	hagl_put_text(u"Kat obrot",78,130, BLACK, font5x7);
	hagl_put_text(u"Kat bierzacy",81-24.5,75-15+10, BLACK, font5x7);
	hagl_put_text(u"Czas obrotu",81-24.5,75-15-10, BLACK, font5x7);
	
		switch (gesture)
	{
		
	case 2:
	hagl_fill_rectangle(1,129,50,159, CYAN);
	hagl_putPtext(u"Kat startowy",2,130, RED, font5x7);
	
	/*zadanie kąta początkowego */
	//GoTo_Start_angle_screen();
	 start_angle = Angle_menu("Kat poczatkowy", current_angle, tryb );
	break;
	
	case 3:
	hagl_fill_rectangle(77,1,77+50,30+1, CYAN);
	hagl_putPtext(u"Powrot",78,2, RED, font5x7);
	 
	Screen_Motor_Steering(gesture_2);
	break;
	case 4:
	hagl_fill_rectangle(77,129,77+50,30+129, CYAN);
	hagl_put_text(u"Kat obrot",78,130, RED, font5x7);
	
	/* ekran do nastawienia kąta obrotu silnika */
	//GoTo_rotate_angle_settings();
	rot_angle = Angle_menu("Obrot", start_angle, tryb );
	break;
	
	case 5 :
	hagl_fill_rectangle(80-24.5,74-15+10,80+24.5,74+15+10, CYAN);
	hagl_put_text(u"Kat biezacy",81-24.5,75-15+10, RED, font5x7);
	
	//odczyt biezacego kata
	Current_angle_screen(current_angle);
	break;
	
	case 6:
	hagl_fill_rectangle(80-24.5,74-15-10,80+24.5,74+15-10, CYAN);
	hagl_put_text(u"Czas obrotu",81-24.5,75-15-10, RED, font5x7);
	
	//ekran do nastawiania czasu obrotu silnika z kierunku A na kierunek B
	GoTo_Motor_rotation_time_screen();
	break;
	}
}


/* panel trybu 1 - nadążanie na kierunek A */
void GoTo_1_mode(uint16_t gesture)
{
	
	/* Menu trybu 1 */
		hagl_fill_rectangle(1,1,50,30, CYAN);
		hagl_putPtext(u"Tryb 1",2,2, BLACK, font6x9);
		
		hagl_fill_rectangle(1,129,50,159, YELLOW);
		hagl_fill_rectangle(77,1,77+50,30+1, YELLOW);
		hagl_fill_rectangle(77,129,77+50,129+30, YELLOW);
		hagl_fill_rectangle(80-24.5,74-15,80+24.5,74+15, YELLOW); //na środku poj.
		
		hagl_put_text(u"Kat startowy",2,130, BLACK, font5x7);
		hagl_put_text(u"Powrot",78,2, BLACK, font5x7);
		hagl_put_text(u"Kat obrot",78,130, BLACK, font5x7);
		hagl_put_text(u"Kat biezacy",81-24.5,75-15, BLACK, font5x7); //na środku poj.
		
			switch (gesture)
		{
			
		case 2:
		hagl_fill_rectangle(1,129,50,159, CYAN);
		hagl_putPtext(u"Kat startowy",2,130, RED, font5x7);
		
		/*zadanie kata poczatkowego */
		 start_angle = Angle_menu("Kat poczatkowy", current_angle, tryb );
		//GoTo_Start_angle_screen();
		break;
		
		case 3:
		hagl_fill_rectangle(77,1,77+50,30+1, CYAN);
		hagl_putPtext(u"Powrot",78,2, RED, font5x7);
		 
		Screen_Motor_Steering(gesture);
		break;
		
		case 4:
		hagl_fill_rectangle(77,129,77+50,30+129, CYAN);
		hagl_put_text(u"Kat obrot",78,130, RED, font5x7);
		
		/* ekran do nastawienia kata obrotu silnika */
		GoTo_rotate_angle_settings();	
		rot_angle = Angle_menu(u"Obrot", start_angle, tryb);
		break;
		
		case 5:
		hagl_fill_rectangle(80-24.5,74-15+10,80+24.5,74+15+10, CYAN);
		hagl_put_text(u"Kat biezacy",81-24.5,75-15+10, RED, font5x7);
			
		//odczyt biezacego kata
		GoTo_Current_angle_screen();
		break;
		}
}

/* funkcja wyświetlająca "animowany potencjometr" 
 gesture_rot_direction - informacja o kierunku obrotu palcem - 1 prawo, 2 - lewo, 0 - brak wykrycia ruchu */
void potentiometer_animation(int gesture_rot_direction, uint16_t Screen_Height, uint16_t Screen_Width)
{
	/* Współrzędne obszaru wyświetlania animacji potencjometru */
	uint16_t pot_area = 50;
	uint16_t x0_pot_area = (Screen_Width - pot_area)/2;
	uint16_t y0_pot_area = (Screen_Height - pot_area)/2;
	uint16_t x1_pot_area = (Screen_Width + pot_area)/2;
	uint16_t y1_pot_area = (Screen_Height + pot_area)/2;
	uint16_t x_c = Screen_Width/2;
	uint16_t y_c = Screen_Height/2;
	/* tablice z punktami na okręgu o promieniu 25 */
	uint16_t x_tab[24] = {0,5,13,18,22,24,25,24,22,18,13,5,0,-5,-13,-18,-22,-24,-25,-24,-22,-18,-13,-5};
	uint16_t y_tab[24] = {25,24,22,18,13,5,0,-5,-13,-18,-22,-24,-25,-24,-22,-18,-13,-5,0,5,13,18,22,24};
	/* okno do łatwego wyświetlania i usuwania obrazu */ 
	hagl_set_clip_window(x0_pot_area, y0_pot_area, x1_pot_area, y1_pot_area );
	/*trzeba mi tu rozrysować kolo o promieniu r w którym będzie mniejsze kółko w innym kolorze obracać się zgodnie/przeciwnie do ruchu wskazówek zegara */
	hagl_fill_circle(x_c,y_c, 25, MAGENTA);
	hagl_draw_vline(x_c,y_c,24,YELLOW);
	
	if(gesture_rot_direction = 2)	// obrót w prawo
	{
	/* narysowanie linii prostej zmieniającej położenie z każdą iteracją */ 
		for(int i =0; i <24; i++)
		{
			hgl_clear_clip_window();
			hagl_fill_circle(x_c,y_c, 25, MAGENTA);
			int x1 = x_c + x_tab[i];
			int y1 = y_c + y_tab [i];
			hagl_draw_line(x_c,y_c, x1, y1, YELLOW);
		}
	}
	/* obrót przeciwnie do ruchu wskazówek zegara */
	if(gesture_rot_direction = 3)
	{
		for(int i = 24; i > 0; i--)
		{
		hgl_clear_clip_window();
		hagl_fill_circle(x_c,y_c, 25, MAGENTA);
		int x1 = x_c + x_tab[i];
		int y1 = y_c + y_tab [i];
		hagl_draw_line(x_c,y_c, x1, y1, YELLOW);
		}
	}
	
}



/* Panel nastawy kąta */
double Angle_menu (const wchar_t *Title, uint16_t current_angle, int Mode )
{
	double angle_set = current_angle; // pobranie info o aktualnym położeniu

	hagl_fill_rectangle(1,1,30,30, CYAN);
	/* wyświetlanie trybu w lewym dolnym rogu */

	hagl_put_text(Mode, 2, 2, BLACK, font6x9);
	hagl_fill_rectangle(1,129,50,159, YELLOW);
	hagl_put_text(*Title, 2, 130, BLACK, font6x9);

	/* wyświetlanie aktualnej wartości kąta na dole na środku ekranu */ 
	hagl_fill_rounded_rectangle(20, 35, 40, 93, 3, CYAN);
	hagl_put_text(current_angle, 22, 37, YELLOW, font6x9);

	if(gesture_rot_direction == 2)		// obroty zgodnie z ruchem wskazówek zegara
		{
		angle_set = angle_set + 1;
		potentiometer_animation( 2, 160, 128);
		}
	if(gesture_rot_direction == 3)		// obroty przeciwnie do ruchu wskazówek zegara
		{
		angle_set == angle_set - 1;
		potentiometer_animation( 3, 160, 128);
		}
	/* powrót pod wpływem dotknięcia prawego dolnego rogu Flicka */ 
	
	if(gesture == 3)
	{
		if( Mode == 0)
		{
			GoTo_0_mode(gesture);
		}
		if (Mode == 1)
		{
			GoTo_1_mode(gesture);
		}
	}
return angle_set;
}
/* Panel odczytu biezacego kata obrotu
   Pobierana informacja o aktualnej pozycji katowej silnika */
void Current_angle_screen(double current_angle)
	{
		/*hagl_fill_rectangle(1,1,50,30, CYAN);
		hagl_putPtext(u"Tryb: " tryb,2,2, BLACK, font6x9);
		nie koniecznie jest to potrzebne xD */

		hagl_fill_rectangle(77,1,77+50,30+1, YELLOW);
		hagl_fill_rectangle(80-50,74-30,80+50,74+30, YELLOW);
		
		hagl_put_text(u"Powrot",78,2, BLACK, font5x7);
		hagl_put_text(current_angle,81-50,75-30,BLACK, font10x14);
		
		switch (gesture)
		{
		case 2:
				hagl_fill_rectangle(77,1,77+50,30+1, CYAN);
				hagl_putPtext(u"Powrot",78,2, RED, font5x7);
				
				/*Powrot do menu glownego */
				GoTo_Start_Screen();
				break;
		}
	}




/* Panel odczytu predkosci katowej
   Pobierana informacja o aktualnej predkosci katowej */
void Screen_Angular_Velocity(int angular_velocity)
	{
		hagl_fill_rectangle(77,1,77+50,30+1, YELLOW);
		hagl_fill_rectangle(80-50,74-30,80+50,74+30, YELLOW);
		
		hagl_put_text(u"Powrot",78,2, BLACK, font5x7);
		hagl_put_text(angular_velocity,81-50,75-30,BLACK, font6x9);
		
		switch (gesture)
		{
		case 2:
				hagl_fill_rectangle(77,1,77+50,30+1, CYAN);
				hagl_putPtext(u"Powrot",78,2, RED, font5x7);
				
				/*Powrot do menu glownego */
				GoTo_Start_Screen();
				break;
		}
	}



/* Panel odczytu katow Eulera
   Pobierana informacja o aktualnej wartosci 3 katow eulera: Xi, Yi, Zi */
void Euler_Angular_Reading_Panel(int Xi, int Yi, int Zi)
	{
		hagl_fill_rectangle(77,1,77+50,30+1, YELLOW);
		
		hagl_fill_rectangle(80-25,74-15,80+25,74+15, YELLOW);
		hagl_fill_rectangle(80-25,74+15+10,80+25,74+15+10+30, YELLOW);
		hagl_fill_rectangle(80-25,74-15-10-30,80+25,74-15-10, YELLOW);
		
		
		hagl_put_text(u"Powrot",78,2, BLACK, font5x7);
		
		hagl_put_text(Yi,81-25,75-15, BLACK, font6x9);
		hagl_put_text(Xi,81-25,75+15+10, BLACK, font6x9);
		hagl_put_text(Zi,81-25,75-15-10-30, BLACK, font6x9);
		
		switch (gesture)
		{
		case 2:
				hagl_fill_rectangle(77,1,77+50,30+1, CYAN);
				hagl_putPtext(u"Powrot",78,2, RED, font5x7);
				
				/*Powrot do menu glownego */
				GoTo_Start_Screen();
				break;
		}
	}

