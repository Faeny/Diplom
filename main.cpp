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
//		printf ("\n���� [%s]:\n", pChild->Value());	
		for (pCont=pChild->FirstChild(); pCont != 0; pCont = pCont->NextSibling())
		{
//			printf ("���� [%s]:\n", pCont->FirstChild()->Value());
			if(strcmp(pCont->FirstChild()->Value(), pAttrib->Value())==0)
			{
				printf ("			��������� �����-��������: [%s],		��������: [%s],		�����-������: [%s]\n", pCont->FirstChild()->Value(), findNode->FirstChild()->Value(), findNode->Value());
				countWord++;
				fNode=findNode->FirstChild();
			}
//			printf ("�������: %s  �����: %s\n", pCont->FirstChild()->Value(), pAttrib->Value());
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

	printf ("\n\n��� 4\n");
	printf ("�������� ��������� �� ������ ����� [%s]\n", pParent->Value());
	printf ("����� ���� �������� �����-������� [%s] �� ����� �������-�����������\n", pParent->Value());	

	for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{		
		printf ("\n\n�����-������ [%s]:  �������� [%s]:\n\n", pParent->Value(), pChild->Value());
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
	printf ("\n\n��� 3\n");
	printf ("����� �����: [%s]\n", findWord);
	
	TiXmlNode* pChild;
	TiXmlText* pText;
/*
	switch ( node_type )
	{
	case TiXmlNode::TINYXML_ELEMENT:
		
		if (strcmp(pChild->Value(), findWord) == 0)
		{
			printf ("������� ����� [%s] �������\n", findWord);
			printf ("����: [%s]\n\n", pChild->Value());
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
			printf ("������� ����� [%s] �������\n", findWord);
//			printf ("����: [%s]\n\n", pChild->Value());
			findNode=pChild;
			getCont(pChild);
		}
		else
		{
			printf ("������� ����� �� �������\n");
			notFind=true;
			return;
		}
	}
/*	
//	printf("\n����� ���������\n");
//	system("pause");

//	pChild=pParent->FirstChild();

	if (strcmp(pChild->Value(), findWord) == 0)
	{
		printf ("������� ����� [%s] �������\n", findWord);
		printf ("����: [%s], ����� ����: %d\n\n\n", pChild->Value(), i);
	}

//	printf("\n����� ��������\n");
//	system("pause");
//
// ��������� ��������, ����� ���� �����, �� ������
	
	if (pParent->Value()==findWord)
	{
		printf ("������� ����� %s �������", findWord);
	}

//	else
//	{
//		printf ("������� ����� %s �� �������", findWord);
//	}

//	printf("\n����� ��������\n");
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
	
	
	
	if (strcmp(pParent->Value(),"��������")==0)
	{
		pElement=pParent->ToElement(); // �������� ��� ���� � ��������
//		printf("\n%s %s", pElement->Value(), pElement->FirstAttribute()->Name());
		if (pElement->FirstAttribute()->QueryIntValue(&iValue)==TIXML_SUCCESS)
			printf( "%s %d\n", pParent->Value(), iValue);
	}
	
	if (strcmp(pParent->Value(),"�����������")==0)
	{
		pElement=pParent->ToElement();
//		printf("\n\n%s %s", pElement->Value(), pElement->FirstAttribute()->Name());
		if (pElement->FirstAttribute()->QueryIntValue(&iValue)==TIXML_SUCCESS)
			printf( "\n	%s %d: ", pParent->Value(), iValue);
	}

	if (strcmp(pParent->Value(),"��������")==0)
	{
		pText=pParent->FirstChild()->ToText(); // �������� ��� ���� � ������
		printf("[%s]\n\n", pText->Value());
	}
	
	if (strcmp(pParent->Value(),"�����")==0)
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
		case "��������":
		{
			printf( "�����: [%s]\n", pParent->Value());
			break;
		}
		case "�����������":
		{
			printf( "�����: [%s]\n", pParent->Value());
			break;
		}
		case "��������":
		{
			pText = pParent->ToText();
			printf( "�����: [%s]\n", pText->Value());
			break;
		}
		case "�����":
		{
			printf( "�����: [%s]\n", pParent->Value());
			break;
		}
		case "�����":
		{
			printf( "�����: [%s]\n", pParent->Value());
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

	printf("\n\n��� 1\n");
	printf("�������� ����� ������� ��������\n");

	if (loadOkay)
	{
		printf("���� [omon.xml] �������� ������!\n");
		system("pause");
		printf("\n\n��� 2\n");
		printf("������� ������� �����: ");
		scanf("%s", findWord);
		findOmon(&XMLOmon);
	}
	else
	{
		printf("������ �������� ����� [omon.xml]\n");
		return;
	}
	printf("\n");
	system("pause");
	printf("\n\n��� 5\n");
	printf("\n�������� ����� ������\n");
	
	if (notFind)
		return;
	
	if (loadOkayText)
	{
		printf("���� [corp.xml] �������� ������!\n");
		system("pause");
		printf ("\n\n��� 6\n");
		printf ("������������� ����� ����� [corp.xml] � ������� � *������������*\n\n\n");
		readXMLfile(&XMLfileText);
	}
	else
	{
		printf("������ �������� ����� [corp.xml]\n");
		return;
	}
}

void taskText()
{
	printf("#########################################################\n");
	printf("#\n");
	printf("#	�������� �����:\n");
	printf("#\n");
	printf("#	���� ������ �������, ��� ��� ��-������ �������.\n");
	printf("#	���� ������ ������� �����������, ������, � � ���������� ��������� ���� ��� � ��������.\n");
	printf("#	�������, �� ����� �������� �������� � ��������� ������������� ��������, ���� ���������, ������� � ������� ����������� ���� �������� ����� ����������.\n");
	printf("#	������� �������� ����: ��������� �������� � �������� ��������.\n");
	printf("#	�� ��� �������� ����� �������� ����� ����� ������� ��� ������� ������, � ����� ����� ����� ��������, ����� �������������� ��������� ���������� �������.\n");
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
		printf("\n\n��� 7\n");
		printf("\n������ ���������� �����������:\n");
		printf("� ������ ������� [%d] ����-���������� �����-������� [%s] � �������� [%s]\n", countWord, findNode->Value(), fNode->Value());
	}

	printf("\n");
	printf("\n");
	system("pause");
	system("cls");
}