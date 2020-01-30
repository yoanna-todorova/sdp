
#include "pch.h"
#include <iostream>
#include "Map.h"

int main()
{
	Junction j1("NDK");
	Junction j2("Arena_Armeec");
	Junction j3("Lion's_Bridge");
	Junction j4("Eagle's_Bridge");
	Junction j5("Alexander_Nevsky_Cathedral");
	Junction j6("Saint_Sofia");
	Junction j7("Saint_Nedelya");
	Junction j8("BSFS");
	Junction j9("Vasil_Levski_Stadium");
	Junction j10("Borisova_Gradina");
	Junction j11("Sofia_Synagogue");
	Junction j12("National_Art_Gallery");
	Junction j13("Sofia_Zoo");
	Junction j14("National_Opera");
	Junction j15("Kopitoto");
	Junction j16("Seven_Saints_Church");
	Junction j17("Vitosha_Boulevard");
	Junction j18("Boyana_church");
	Junction j19("Ivan_Vazov_Nat_Theatre");
	Junction j20("Russian_Church");
	Junction j21("Popa");
	Junction j22("5Kiusheta");
	Junction j23("Archaelogical_Museum");
	
	
	Map m1;
	m1.addJunction(&j1);
	m1.addJunction(&j2);
	m1.addJunction(&j3);
	m1.addJunction(&j4);
	m1.addJunction(&j5);
	m1.addJunction(&j6);
	m1.addJunction(&j7);
	m1.addJunction(&j8);
	m1.addJunction(&j9);
	m1.addJunction(&j10);
	m1.addJunction(&j11);
	m1.addJunction(&j12);
	m1.addJunction(&j13);
	m1.addJunction(&j14);
	m1.addJunction(&j15);
	m1.addJunction(&j16);
	m1.addJunction(&j17);
	m1.addJunction(&j18);
	m1.addJunction(&j19);
	m1.addJunction(&j20);
	m1.addJunction(&j21);
	m1.addJunction(&j22);
	m1.addJunction(&j23);
	
	/*//Ïðîâåðêà äàëè èìà ïúò ìåæäó äâå çàäàäåíè êðúñòîâèùà

	m1.addStreet(&j1, &j2, 120);
	m1.addStreet(&j2, &j5, 120);
	m1.addStreet(&j5, &j7, 120);
	m1.addStreet(&j7, &j3, 120);
	m1.addStreet(&j3, &j20, 120);
	m1.addStreet(&j20, &j22, 120);
	m1.addStreet(&j4, &j21, 115);

	//std::cout << m1.hasPath(&j1, &j22) << std::endl; //èìà ïúò ìåæäó òåçè
	//std::cout << m1.hasPath(&j1, &j21) << std::endl; //íÿìà ïúò ìåæäó òåçè

*/

	//Íàìèðàíå íà òðèòå íàé - êðàòêè ïúòÿ ìåæäó äâå çàäàäåíè êðúñòîâèùà.

	m1.addStreet(&j1, &j7, 5);
	m1.addStreet(&j7, &j5, 5);
	m1.addStreet(&j5, &j11, 5);
	m1.addStreet(&j11, &j15, 10);
	m1.addStreet(&j15, &j3, 70);
	m1.addStreet(&j11, &j3, 5);
	m1.addStreet(&j5, &j3, 70);
	m1.addStreet(&j1, &j3, 220);
	m1.addStreet(&j1, &j5, 85);
	m1.addStreet(&j1, &j4, 110);
	m1.addStreet(&j4, &j3, 15);
	m1.addStreet(&j1, &j17, 30);
	m1.addStreet(&j17, &j3, 15);

	std::cout << "Three shortest: ";
	std::cout << " " << std::endl;
	m1.ThreeShortestPath(&j1, &j3);
	std::cout << " " << std::endl;

	//Ïðè íàëè÷èåòî íà çàòâîðåíè êðúñòîâèùà(êîèòî äà áúäàò ïîäàâàíè êàòî ñïèñúê) äà ñå íàìåðè òðèòå àëòåðíàòèâíè íàé - êðàòêè ïúòèùà 
	//ìåæäó äâå çàäàäåíè êðúñòîâèùà.
	
	std::list<Junction*> closed = { &j7,&j5,&j15};
	std::cout << "Three alternative shortest: ";
	std::cout << " " << std::endl;
	m1.ThreeAlternativeShortestPath(&j1, &j3, closed);
	m1.writeOn();

	/*
//Ïðîâåðêà äàëè ïðè äàäåíî êðúñòîâèùå çà íà÷àëíà òî÷êà å âúçìîæíî äà îáèêîëèì ÷àñò îò ãðàäà è âúðíåì îáðàòíî òàì, îòêúäåòî ñìå òðúãíàëè
	m1.addStreet(&j1, &j2, 120);
	m1.addStreet(&j2, &j5, 120);
	m1.addStreet(&j5, &j7, 120);
	m1.addStreet(&j7, &j3, 120);
	m1.addStreet(&j3, &j20, 120);
	m1.addStreet(&j20, &j22, 120);
	m1.addStreet(&j22, &j1, 115);
	m1.addStreet(&j8, &j2, 180);

	std::cout<<m1.canMakeCircuit(&j3)<<std::endl; //ïðàâè îáèêîëêà
	std::cout << m1.canMakeCircuit(&j8); // íå ïðàâè
	*/


	/*//Ïðîâåðêà äàëè ìîæåì äà íàïðàâèì ïúëíà òóðèñòè÷åñêà îáèêîëêà íà âñè÷êè óëèöè áåç äà ìèíàâàìå ïî åäíà è ñúùà óëèöà äâà ïúòè. 
	//Àêî òàêàâà îáèêîëêà å âúçìîæíà, äà ñå íàìåðè ìàðøðóòà íà òàçè îáèêîëêà.
	m1.addStreet(&j1, &j2, 50);
	m1.addStreet(&j2, &j3, 50);
	m1.addStreet(&j3, &j4, 50);
	m1.addStreet(&j4, &j5, 50);
	m1.addStreet(&j5, &j6, 50);
	m1.addStreet(&j6, &j7, 50);
	m1.addStreet(&j7, &j8, 50);
	m1.addStreet(&j8, &j9, 50);
	m1.addStreet(&j9, &j10, 50);
	m1.addStreet(&j10, &j11, 50);
	m1.addStreet(&j11, &j12, 50);
	m1.addStreet(&j12, &j13, 50);
	m1.addStreet(&j13, &j14, 50);
	m1.addStreet(&j14, &j15, 50);
	m1.addStreet(&j15, &j16, 50);
	m1.addStreet(&j16, &j17, 50);
	m1.addStreet(&j17, &j18, 50);
	m1.addStreet(&j18, &j19, 50);
	m1.addStreet(&j19, &j20, 50);
	m1.addStreet(&j20, &j21, 50);
	m1.addStreet(&j21, &j22, 50);
	m1.addStreet(&j22, &j23, 50);
	m1.addStreet(&j23, &j1, 50);

	//m1.makeTouristCircuit();
	*/

/*	
//Ïðîâåðêà äàëè å âúçìîæíî äà ñòèãíåì îò äàäåíî êðúñòîâèùå äî âñè÷êè îñòàíàëè
	m1.addStreet(&j1, &j2, 50);
	m1.addStreet(&j1, &j3, 50);
	m1.addStreet(&j1, &j4, 50);
	m1.addStreet(&j1, &j5, 50);
	m1.addStreet(&j1, &j6, 50);
	m1.addStreet(&j1, &j7, 50);
	m1.addStreet(&j1, &j8, 50);
	m1.addStreet(&j1, &j9, 50);
	m1.addStreet(&j1, &j10, 50);
	m1.addStreet(&j1, &j11, 50);
	m1.addStreet(&j1, &j12, 50);
	m1.addStreet(&j1, &j13, 50);
	m1.addStreet(&j1, &j14, 50);
	m1.addStreet(&j1, &j15, 50);
	m1.addStreet(&j1, &j16, 50);
	m1.addStreet(&j1, &j17, 50);
	m1.addStreet(&j1, &j18, 50);
	m1.addStreet(&j1, &j19, 50);
	m1.addStreet(&j1, &j20, 50);
	m1.addStreet(&j1, &j21, 50);
	m1.addStreet(&j1, &j22, 50);
	m1.addStreet(&j1, &j23, 50);
	std::cout<<m1.canReachAnywhere(&j1);
*/

/*
//Íàìèðàíå íà âñè÷êè çàäúíåíè óëèöè (åäíîïîñî÷íà óëèöà êîÿòî ñâúðøâà â êðúñòîâèùå îò êîåòî íå èçëèçàò óëèöè). 
//Óëèöèòå îïèñâàìå êàòî äâîéêà îò èìåíàòà íà êðúñòîâèùåòî îò êîåòî çàïî÷âà è êðúñòîâèùåòî, êúäåòî ñâúðøâà.
m1.addStreet(&j1, &j2, 50);
m1.addStreet(&j3, &j4, 50);
m1.addStreet(&j5, &j6, 50);
m1.addStreet(&j7, &j8, 50);

m1.findAllBlindAlleys();
*/


}

