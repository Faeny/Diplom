#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <stdlib.h>

// tinyXML
#include <tinyxml.cpp>
#include <tinyxmlerror.cpp>
#include <tinyxmlparser.cpp>
#include <tinystr.cpp>
#include <tinystr.h>
#include <tinyxml.h>

using namespace std;

bool notFind=false;
char findWord[255];
TiXmlNode* findNode;
TiXmlNode* fNode;
int countWord;

const char* wordcmp(TiXmlNode* pParent)
{
	TiXmlNode* pChild;
	TiXmlNode* pCont;
	TiXmlElement* pElement;
	TiXmlAttribute* pAttrib;	
	
	pElement=pParent->ToElement();
	pAttrib=pElement->LastAttribute();
	
	if (!pAttrib) return "-";
	
	for (pChild=findNode->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{		
//		printf ("\nУзел [%s]:\n", pChild->Value());	
		for (pCont=pChild->FirstChild(); pCont != 0; pCont = pCont->NextSibling())
		{
//			printf ("Узел [%s]:\n", pCont->FirstChild()->Value());
			if(strcmp(pCont->FirstChild()->Value(), pAttrib->Value())==0)
			{
				printf ("			Найденное слово-контекст: [%s],		значение: [%s],		слово-омоним: [%s]\n", pCont->FirstChild()->Value(), findNode->FirstChild()->Value(), findNode->Value());
				countWord++;
				fNode=findNode->FirstChild();
			}
//			printf ("Омонимы: %s  Слово: %s\n", pCont->FirstChild()->Value(), pAttrib->Value());
		}
	}
	return "olo";
}

void getCont(TiXmlNode* pParent)
{
	if ( !pParent ) return;
	TiXmlNode* pChild;
	TiXmlNode* pCont;
	TiXmlText* pText;
	
	system("pause");

	printf ("\n\nШаг 4\n");
	printf ("Сохрание указателя на адреса узела [%s]\n", pParent->Value());
	printf ("Вывод всех значений слова-омонима [%s] со всеми словами-контекстами\n", pParent->Value());	

	for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{		
		printf ("\n\nСлово-омоним [%s]:  значение [%s]:\n\n", pParent->Value(), pChild->Value());
		for ( pCont = pChild->FirstChild(); pCont != 0; pCont = pCont->NextSibling())
		{
			pText = pCont->FirstChild()->ToText();
			printf ("	%s\n", pText->Value());			
		}		
	}
}

void findOmon(TiXmlNode* pParent)
{
	if (!pParent)
		return;
//	system("pause");
	printf ("\n\nШаг 3\n");
	printf ("Поиск слова: [%s]\n", findWord);
	
	TiXmlNode* pChild;
	TiXmlText* pText;
/*
	switch ( node_type )
	{
	case TiXmlNode::TINYXML_ELEMENT:
		
		if (strcmp(pChild->Value(), findWord) == 0)
		{
			printf ("Искомое слово [%s] найдено\n", findWord);
			printf ("Узел: [%s]\n\n", pChild->Value());
		}

		
//		printf( "Element [%s]", pParent->Value() );
//		num=dump_attribs_to_stdout(pParent->ToElement(), indent+1);
/*
		switch(num)
		{
			case 0:  printf( " (No attributes)"); break;
			case 1:  printf( "%s1 attribute", getIndentAlt(indent)); break;
			default: printf( "%s%d attributes", getIndentAlt(indent), num); break;
		}

		break;

	case TiXmlNode::TINYXML_TEXT:
		pText = pParent->ToText();
//		printf( "Text: [%s]", pText->Value() );
		break;

	default:
		break;
	}
*/	
	for ( pChild = pParent->LastChild()->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
		if (strcmp(pChild->Value(), findWord) == 0)
		{
			printf ("Искомое слово [%s] найдено\n", findWord);
//			printf ("Узел: [%s]\n\n", pChild->Value());
			findNode=pChild;
			getCont(pChild);
		}
		else
		{
			printf ("Искомое слово не найдено\n");
			notFind=true;
			return;
		}
	}
/*	
//	printf("\nперед проверкой\n");
//	system("pause");

//	pChild=pParent->FirstChild();

	if (strcmp(pChild->Value(), findWord) == 0)
	{
		printf ("Искомое слово [%s] найдено\n", findWord);
		printf ("Узел: [%s], номер узла: %d\n\n\n", pChild->Value(), i);
	}

//	printf("\nпосле проверки\n");
//	system("pause");
//
// нерабочая проверка, пусть пока будет, на всякий
	
	if (pParent->Value()==findWord)
	{
		printf ("Искомое слово %s найдено", findWord);
	}

//	else
//	{
//		printf ("Искомое слово %s не найдено", findWord);
//	}

//	printf("\nпосле проверки\n");
//	system("pause");


	for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
		findElem(pChild);
	}
*/
}

void readXMLfile(TiXmlNode* pParent)
{
	if (!pParent) return;
	
	TiXmlNode* pChild;
	TiXmlElement* pElement;
	TiXmlAttribute* pAttrib;
	TiXmlText* pText;	
	int iValue;
	
	
	
	if (strcmp(pParent->Value(),"параграф")==0)
	{
		pElement=pParent->ToElement(); // приводим тип узла к элементу
//		printf("\n%s %s", pElement->Value(), pElement->FirstAttribute()->Name());
		if (pElement->FirstAttribute()->QueryIntValue(&iValue)==TIXML_SUCCESS)
			printf( "%s %d\n", pParent->Value(), iValue);
	}
	
	if (strcmp(pParent->Value(),"предложение")==0)
	{
		pElement=pParent->ToElement();
//		printf("\n\n%s %s", pElement->Value(), pElement->FirstAttribute()->Name());
		if (pElement->FirstAttribute()->QueryIntValue(&iValue)==TIXML_SUCCESS)
			printf( "\n	%s %d: ", pParent->Value(), iValue);
	}

	if (strcmp(pParent->Value(),"источник")==0)
	{
		pText=pParent->FirstChild()->ToText(); // приводим тип узла к тексту
		printf("[%s]\n\n", pText->Value());
	}
	
	if (strcmp(pParent->Value(),"слово")==0)
	{
		pElement=pParent->ToElement();
		pText=pParent->FirstChild()->ToText();
//		printf("\n%s %s", pElement->Value(), pElement->FirstAttribute()->Name());
//		if (pElement->FirstAttribute()->QueryIntValue(&iValue)==TIXML_SUCCESS)
//			printf( " %d\n", iValue);
//		printf("\n%s\n", pText->Value());
		
		wordcmp(pParent);
	}

/*	
	switch(pParent->Value())
	{
		case "параграф":
		{
			printf( "Текст: [%s]\n", pParent->Value());
			break;
		}
		case "предложение":
		{
			printf( "Текст: [%s]\n", pParent->Value());
			break;
		}
		case "источник":
		{
			pText = pParent->ToText();
			printf( "Текст: [%s]\n", pText->Value());
			break;
		}
		case "слова":
		{
			printf( "Текст: [%s]\n", pParent->Value());
			break;
		}
		case "слово":
		{
			printf( "Текст: [%s]\n", pParent->Value());
			break;
		}		
		default:
			break;
	}
*/

	for ( pChild = pParent->FirstChildElement(); pChild != 0; pChild = pChild->NextSiblingElement()) 
	{
		readXMLfile(pChild);
	}
}

void loadXMLfile ()
{
	TiXmlDocument XMLOmon("omon.xml");
	TiXmlDocument XMLfileText("corp.xml");

	bool loadOkay = XMLOmon.LoadFile();
	bool loadOkayText = XMLfileText.LoadFile();

	printf("\n\nШаг 1\n");
	printf("Загрузка файла словаря омонимов\n");

	if (loadOkay)
	{
		printf("Файл [omon.xml] загружен удачно!\n");
		system("pause");
		printf("\n\nШаг 2\n");
		printf("Введите искомое слово: ");
		scanf("%s", findWord);
		findOmon(&XMLOmon);
	}
	else
	{
		printf("Ошибка загрузки файла [omon.xml]\n");
		return;
	}
	printf("\n");
	system("pause");
	printf("\n\nШаг 5\n");
	printf("\nЗагрузка файла текста\n");
	
	if (notFind)
		return;
	
	if (loadOkayText)
	{
		printf("Файл [corp.xml] загружен удачно!\n");
		system("pause");
		printf ("\n\nШаг 6\n");
		printf ("Иттерационный обход файла [corp.xml] в глубину с *бэктрекингом*\n\n\n");
		readXMLfile(&XMLfileText);
	}
	else
	{
		printf("Ошибка загрузки файла [corp.xml]\n");
		return;
	}
}

void taskText()
{
	printf("#########################################################\n");
	printf("#\n");
	printf("#	Исходный текст:\n");
	printf("#\n");
	printf("#	Косы бывают разными, все они по-своему красивы.\n");
	printf("#	Косы делают девушку женственной, нежной, а в тенденциях последней моды еще и стильной.\n");
	printf("#	Кончено, не стоит избегать причесок с плетением длинноволосым девушкам, ведь правильно, красиво и стильно заплетенная коса выглядит очень современно.\n");
	printf("#	Косички подходят всем: маленьким девочкам и взрослым девушкам.\n");
	printf("#	Но для создания таких причесок нужно иметь длинные или средние волосы, а также знать схему плетения, чтобы самостоятельно создавать прекрасные укладки.\n");
	printf("#\n");
	printf("#########################################################\n");
	printf("\n");
	printf("\n");
	system("pause");
}

void main()
{
	system("cls");

	setlocale (LC_ALL,"1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	taskText();
	loadXMLfile();
	
	printf("\n");
	system("pause");
	if (!notFind)
	{
		printf("\n\nШаг 7\n");
		printf("\nАнализ полученных результатов:\n");
		printf("В тексте найдено [%d] слов-контекстов слова-омонима [%s] в значении [%s]\n", countWord, findNode->Value(), fNode->Value());
	}

	printf("\n");
	printf("\n");
	system("pause");
	system("cls");
}