#include "ftclient.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include <atomic>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <cstdio>
#endif

using namespace std;

//tube name
#define TUBE_NAME "testtube"

#define PKG_HEADER "mtcd"

typedef long long DATA_SIZE;

//tube client
int main(){

	const char* data = "ThispageshowsexamplesofmessagesformattedusingJSON(JavaScriptObjectNotation).{\"glossary\":{\"title\":\"exampleglossary\",\"GlossDiv\":{\"title\":\"S\",\"GlossList\":{\"GlossEntry\":{\"ID\":\"SGML\",\"SortAs\":\"SGML\",\"GlossTerm\":\"StandardGeneralizedMarkupLanguage\",\"Acronym\":\"SGML\",\"Abbrev\":\"ISO8879:1986\",\"GlossDef\":{\"para\":\"Ameta-markuplanguage,usedtocreatemarkuplanguagessuchasDocBook.\",\"GlossSeeAlso\":[\"GML\",\"XML\"]},\"GlossSee\":\"markup\"}}}}}ThesametextexpressedasXML:<!DOCTYPEglossaryPUBLIC\"-//OASIS//DTDDocBookV3.1//EN\"><glossary><title>exampleglossary</title><GlossDiv><title>S</title><GlossList><GlossEntryID=\"SGML\"SortAs=\"SGML\"><GlossTerm>StandardGeneralizedMarkupLanguage</GlossTerm><Acronym>SGML</Acronym><Abbrev>ISO8879:1986</Abbrev><GlossDef><para>Ameta-markuplanguage,usedtocreatemarkuplanguagessuchasDocBook.</para><GlossSeeAlsoOtherTerm=\"GML\"><GlossSeeAlsoOtherTerm=\"XML\"></GlossDef><GlossSeeOtherTerm=\"markup\"></GlossEntry></GlossList></GlossDiv></glossary>{\"menu\":{\"id\":\"file\",\"value\":\"File\",\"popup\":{\"menuitem\":[{\"value\":\"New\",\"onclick\":\"CreateNewDoc()\"},{\"value\":\"Open\",\"onclick\":\"OpenDoc()\"},{\"value\":\"Close\",\"onclick\":\"CloseDoc()\"}]}}}ThesametextexpressedasXML:<menuid=\"file\"value=\"File\"><popup><menuitemvalue=\"New\"onclick=\"CreateNewDoc()\"/><menuitemvalue=\"Open\"onclick=\"OpenDoc()\"/><menuitemvalue=\"Close\"onclick=\"CloseDoc()\"/></popup></menu>{\"widget\":{\"debug\":\"on\",\"window\":{\"title\":\"SampleKonfabulatorWidget\",\"name\":\"main_window\",\"width\":500,\"height\":500},\"image\":{\"src\":\"Images/Sun.png\",\"name\":\"sun1\",\"hOffset\":250,\"vOffset\":250,\"alignment\":\"center\"},\"text\":{\"data\":\"ClickHere\",\"size\":36,\"style\":\"bold\",\"name\":\"text1\",\"hOffset\":250,\"vOffset\":100,\"alignment\":\"center\",\"onMouseUp\":\"sun1.opacity=(sun1.opacity/100)*90;\"}}}ThesametextexpressedasXML:<widget><debug>on</debug><windowtitle=\"SampleKonfabulatorWidget\"><name>main_window</name><width>500</width><height>500</height></window><imagesrc=\"Images/Sun.png\"name=\"sun1\"><hOffset>250</hOffset><vOffset>250</vOffset><alignment>center</alignment></image><textdata=\"ClickHere\"size=\"36\"style=\"bold\"><name>text1</name><hOffset>250</hOffset><vOffset>100</vOffset><alignment>center</alignment><onMouseUp>sun1.opacity=(sun1.opacity/100)*90;</onMouseUp></text></widget>{\"web-app\":{\"servlet\":[{\"servlet-name\":\"cofaxCDS\",\"servlet-class\":\"org.cofax.cds.CDSServlet\",\"init-param\":{\"configGlossary:installationAt\":\"Philadelphia,PA\",\"configGlossary:adminEmail\":\"ksm@pobox.com\",\"configGlossary:poweredBy\":\"Cofax\",\"configGlossary:poweredByIcon\":\"/images/cofax.gif\",\"configGlossary:staticPath\":\"/content/static\",\"templateProcessorClass\":\"org.cofax.WysiwygTemplate\",\"templateLoaderClass\":\"org.cofax.FilesTemplateLoader\",\"templatePath\":\"templates\",\"templateOverridePath\":\"\",\"defaultListTemplate\":\"listTemplate.htm\",\"defaultFileTemplate\":\"articleTemplate.htm\",\"useJSP\":false,\"jspListTemplate\":\"listTemplate.jsp\",\"jspFileTemplate\":\"articleTemplate.jsp\",\"cachePackageTagsTrack\":200,\"cachePackageTagsStore\":200,\"cachePackageTagsRefresh\":60,\"cacheTemplatesTrack\":100,\"cacheTemplatesStore\":50,\"cacheTemplatesRefresh\":15,\"cachePagesTrack\":200,\"cachePagesStore\":100,\"cachePagesRefresh\":10,\"cachePagesDirtyRead\":10,\"searchEngineListTemplate\":\"forSearchEnginesList.htm\",\"searchEngineFileTemplate\":\"forSearchEngines.htm\",\"searchEngineRobotsDb\":\"WEB-INF/robots.db\",\"useDataStore\":true,\"dataStoreClass\":\"org.cofax.SqlDataStore\",\"redirectionClass\":\"org.cofax.SqlRedirection\",\"dataStoreName\":\"cofax\",\"dataStoreDriver\":\"com.microsoft.jdbc.sqlserver.SQLServerDriver\",\"dataStoreUrl\":\"jdbc:microsoft:sqlserver://LOCALHOST:1433;DatabaseName=goon\",\"dataStoreUser\":\"sa\",\"dataStorePassword\":\"dataStoreTestQuery\",\"dataStoreTestQuery\":\"SETNOCOUNTON;selecttest='test';\",\"dataStoreLogFile\":\"/usr/local/tomcat/logs/datastore.log\",\"dataStoreInitConns\":10,\"dataStoreMaxConns\":100,\"dataStoreConnUsageLimit\":100,\"dataStoreLogLevel\":\"debug\",\"maxUrlLength\":500}},{\"servlet-name\":\"cofaxEmail\",\"servlet-class\":\"org.cofax.cds.EmailServlet\",\"init-param\":{\"mailHost\":\"mail1\",\"mailHostOverride\":\"mail2\"}},{\"servlet-name\":\"cofaxAdmin\",\"servlet-class\":\"org.cofax.cds.AdminServlet\"},{\"servlet-name\":\"fileServlet\",\"servlet-class\":\"org.cofax.cds.FileServlet\"},{\"servlet-name\":\"cofaxTools\",\"servlet-class\":\"org.cofax.cms.CofaxToolsServlet\",\"init-param\":{\"templatePath\":\"toolstemplates/\",\"log\":1,\"logLocation\":\"/usr/local/tomcat/logs/CofaxTools.log\",\"logMaxSize\":\"\",\"dataLog\":1,\"dataLogLocation\":\"/usr/local/tomcat/logs/dataLog.log\",\"dataLogMaxSize\":\"\",\"removePageCache\":\"/content/admin/remove?cache=pages&id=\",\"removeTemplateCache\":\"/content/admin/remove?cache=templates&id=\",\"fileTransferFolder\":\"/usr/local/tomcat/webapps/content/fileTransferFolder\",\"lookInContext\":1,\"adminGroupID\":4,\"betaServer\":true}}],\"servlet-mapping\":{\"cofaxCDS\":\"/\",\"cofaxEmail\":\"/cofaxutil/aemail/*\",\"cofaxAdmin\":\"/admin/*\",\"fileServlet\":\"/static/*\",\"cofaxTools\":\"/tools/*\"},\"taglib\":{\"taglib-uri\":\"cofax.tld\",\"taglib-location\":\"/WEB-INF/tlds/cofax.tld\"}}}ThesamefileexpressedasXML:<?xmlversion=\"1.0\"encoding=\"ISO-8859-1\"?><!DOCTYPEweb-appPUBLIC\"-//SunMicrosystems,Inc.//DTDWebApplication2.2//EN\"\"http://java.sun.com/j2ee/dtds/web-app_2.2.dtd\"><web-app><servlet><servlet-name>cofaxCDS</servlet-name><servlet-class>org.cofax.cds.CDSServlet</servlet-class><init-param><param-name>configGlossary:installationAt</param-name><param-value>Philadelphia,PA</param-value></init-param><init-param><param-name>configGlossary:adminEmail</param-name><param-value>ksm@pobox.com</param-value></init-param><init-param><param-name>configGlossary:poweredBy</param-name><param-value>Cofax</param-value></init-param><init-param><param-name>configGlossary:poweredByIcon</param-name><param-value>/images/cofax.gif</param-value></init-param><init-param><param-name>configGlossary:staticPath</param-name><param-value>/content/static</param-value></init-param><init-param><param-name>templateProcessorClass</param-name><param-value>org.cofax.WysiwygTemplate</param-value></init-param><init-param><param-name>templateLoaderClass</param-name><param-value>org.cofax.FilesTemplateLoader</param-value></init-param><init-param><param-name>templatePath</param-name><param-value>templates</param-value></init-param><init-param><param-name>templateOverridePath</param-name><param-value></param-value></init-param><init-param><param-name>defaultListTemplate</param-name><param-value>listTemplate.htm</param-value></init-param><init-param><param-name>defaultFileTemplate</param-name><param-value>articleTemplate.htm</param-value></init-param><init-param><param-name>useJSP</param-name><param-value>false</param-value></init-param><init-param><param-name>jspListTemplate</param-name><param-value>listTemplate.jsp</param-value></init-param><init-param><param-name>jspFileTemplate</param-name><param-value>articleTemplate.jsp</param-value></init-param><init-param><param-name>cachePackageTagsTrack</param-name><param-value>200</param-value></init-param><init-param><param-name>cachePackageTagsStore</param-name><param-value>200</param-value></init-param><init-param><param-name>cachePackageTagsRefresh</param-name><param-value>60</param-value></init-param><init-param><param-name>cacheTemplatesTrack</param-name><param-value>100</param-value></init-param><init-param><param-name>cacheTemplatesStore</param-name><param-value>50</param-value></init-param><init-param><param-name>cacheTemplatesRefresh</param-name><param-value>15</param-value></init-param><init-param><param-name>cachePagesTrack</param-name><param-value>200</param-value></init-param><init-param><param-name>cachePagesStore</param-name><param-value>100</param-value></init-param><init-param><param-name>cachePagesRefresh</param-name><param-value>10</param-value></init-param><init-param><param-name>cachePagesDirtyRead</param-name><param-value>10</param-value></init-param><init-param><param-name>searchEngineListTemplate</param-name><param-value>forSearchEnginesList.htm</param-value></init-param><init-param><param-name>searchEngineFileTemplate</param-name><param-value>forSearchEngines.htm</param-value></init-param><init-param><param-name>searchEngineRobotsDb</param-name><param-value>WEB-INF/robots.db</param-value></init-param><init-param><param-name>useDataStore</param-name><param-value>true</param-value></init-param><init-param><param-name>dataStoreClass</param-name><param-value>org.cofax.SqlDataStore</param-value></init-param><init-param><param-name>redirectionClass</param-name><param-value>org.cofax.SqlRedirection</param-value></init-param><init-param><param-name>dataStoreName</param-name><param-value>cofax</param-value></init-param><init-param><param-name>dataStoreDriver</param-name><param-value>com.microsoft.jdbc.sqlserver.SQLServerDriver</param-value></init-param><init-param><param-name>dataStoreUrl</param-name><param-value>jdbc:microsoft:sqlserver://LOCALHOST:1433;DatabaseName=goon</param-value></init-param><init-param><param-name>dataStoreUser</param-name><param-value>sa</param-value></init-param><init-param><param-name>dataStorePassword</param-name><param-value></param-value></init-param><init-param><param-name>dataStoreTestQuery</param-name><param-value>SETNOCOUNTON;selecttest='test';</param-value></init-param><init-param><param-name>dataStoreLogFile</param-name><param-value>/usr/local/tomcat/logs/datastore.log</param-value></init-param><init-param><param-name>dataStoreInitConns</param-name><param-value>10</param-value></init-param><init-param><param-name>dataStoreMaxConns</param-name><param-value>100</param-value></init-param><init-param><param-name>dataStoreConnUsageLimit</param-name><param-value>100</param-value></init-param><init-param><param-name>dataStoreLogLevel</param-name><param-value>debug</param-value></init-param><init-param><param-name>maxUrlLength</param-name><param-value>500</param-value></init-param></servlet><servlet><servlet-name>cofaxEmail</servlet-name><servlet-class>org.cofax.cds.EmailServlet</servlet-class><init-param><param-name>mailHost</param-name><param-value>mail1</param-value></init-param><init-param><param-name>mailHostOverride</param-name><param-value>mail2</param-value></init-param></servlet><servlet><servlet-name>cofaxAdmin</servlet-name><servlet-class>org.cofax.cds.AdminServlet</servlet-class></servlet><servlet><servlet-name>fileServlet</servlet-name><servlet-class>org.cofax.cds.FileServlet</servlet-class></servlet><servlet><servlet-name>cofaxTools</servlet-name><servlet-class>org.cofax.cms.CofaxToolsServlet</servlet-class><init-param><param-name>templatePath</param-name><param-value>toolstemplates/</param-value></init-param><init-param><param-name>log</param-name><param-value>1</param-value></init-param><init-param><param-name>logLocation</param-name><param-value>/usr/local/tomcat/logs/CofaxTools.log</param-value></init-param><init-param><param-name>logMaxSize</param-name><param-value></param-value></init-param><init-param><param-name>dataLog</param-name><param-value>1</param-value></init-param><init-param><param-name>dataLogLocation</param-name><param-value>/usr/local/tomcat/logs/dataLog.log</param-value></init-param><init-param><param-name>dataLogMaxSize</param-name><param-value></param-value></init-param><init-param><param-name>removePageCache</param-name><param-value>/content/admin/remove?cache=pages&id=</param-value></init-param><init-param><param-name>removeTemplateCache</param-name><param-value>/content/admin/remove?cache=templates&id=</param-value></init-param><init-param><param-name>fileTransferFolder</param-name><param-value>/usr/local/tomcat/webapps/content/fileTransferFolder</param-value></init-param><init-param><param-name>lookInContext</param-name><param-value>1</param-value></init-param><init-param><param-name>adminGroupID</param-name><param-value>4</param-value></init-param><init-param><param-name>betaServer</param-name><param-value>true</param-value></init-param></servlet><servlet-mapping><servlet-name>cofaxCDS</servlet-name><url-pattern>/</url-pattern></servlet-mapping><servlet-mapping><servlet-name>cofaxEmail</servlet-name><url-pattern>/cofaxutil/aemail/*</url-pattern></servlet-mapping><servlet-mapping><servlet-name>cofaxAdmin</servlet-name><url-pattern>/admin/*</url-pattern></servlet-mapping><servlet-mapping><servlet-name>fileServlet</servlet-name><url-pattern>/static/*</url-pattern></servlet-mapping><servlet-mapping><servlet-name>cofaxTools</servlet-name><url-pattern>/tools/*</url-pattern></servlet-mapping><taglib><taglib-uri>cofax.tld</taglib-uri><taglib-location>/WEB-INF/tlds/cofax.tld</taglib-location></taglib></web-app>Theactionandlabelvaluesonlyneedtobeprovidediftheyarenotthesameastheid.{\"menu\":{\"header\":\"SVGViewer\",\"items\":[{\"id\":\"Open\"},{\"id\":\"OpenNew\",\"label\":\"OpenNew\"},null,{\"id\":\"ZoomIn\",\"label\":\"ZoomIn\"},{\"id\":\"ZoomOut\",\"label\":\"ZoomOut\"},{\"id\":\"OriginalView\",\"label\":\"OriginalView\"},null,{\"id\":\"Quality\"},{\"id\":\"Pause\"},{\"id\":\"Mute\"},null,{\"id\":\"Find\",\"label\":\"Find...\"},{\"id\":\"FindAgain\",\"label\":\"FindAgain\"},{\"id\":\"Copy\"},{\"id\":\"CopyAgain\",\"label\":\"CopyAgain\"},{\"id\":\"CopySVG\",\"label\":\"CopySVG\"},{\"id\":\"ViewSVG\",\"label\":\"ViewSVG\"},{\"id\":\"ViewSource\",\"label\":\"ViewSource\"},{\"id\":\"SaveAs\",\"label\":\"SaveAs\"},null,{\"id\":\"Help\"},{\"id\":\"About\",\"label\":\"AboutAdobeCVGViewer...\"}]}}ThesamemessageexpressedasXML:<menu><header>AdobeSVGViewer</header><itemaction=\"Open\"id=\"Open\">Open</item><itemaction=\"OpenNew\"id=\"OpenNew\">OpenNew</item><separator/><itemaction=\"ZoomIn\"id=\"ZoomIn\">ZoomIn</item><itemaction=\"ZoomOut\"id=\"ZoomOut\">ZoomOut</item><itemaction=\"OriginalView\"id=\"OriginalView\">OriginalView</item><separator/><itemaction=\"Quality\"id=\"Quality\">Quality</item><itemaction=\"Pause\"id=\"Pause\">Pause</item><itemaction=\"Mute\"id=\"Mute\">Mute</item><separator/><itemaction=\"Find\"id=\"Find\">Find...</item><itemaction=\"FindAgain\"id=\"FindAgain\">FindAgain</item><itemaction=\"Copy\"id=\"Copy\">Copy</item><itemaction=\"CopyAgain\"id=\"CopyAgain\">CopyAgain</item><itemaction=\"CopySVG\"id=\"CopySVG\">CopySVG</item><itemaction=\"ViewSVG\"id=\"ViewSVG\">ViewSVG</item><itemaction=\"ViewSource\"id=\"ViewSource\">ViewSource</item><itemaction=\"SaveAs\"id=\"SaveAs\">SaveAs</item><separator/><itemaction=\"Help\"id=\"Help\">Help</item><itemaction=\"About\"id=\"About\">AboutAdobeCVGViewer...</item></menu>";

	firetube::ResultStatus createResult = firetube::ResultStatus::RS_SUCCESS;
	firetube::FireTubeClient* client = firetube::FireTubeClient::createClient(TUBE_NAME,&createResult);
	
	//check if client is null
	if (client == NULL)
	{
		cout << "create client fail." << endl;
#ifdef _WIN32
		system("pause");
#else
		cout << "Press Enter to Continue..." << endl;
		char ccc = getchar();
#endif
		return -1;
	}

	//client read data onece
	char buffer[1024];
	int readNum = 0;
	//recv data
	readNum = client->read(buffer,1024);
	if(client->getStatus() != firetube::TubeStatus::TS_READY){
		cout << "client status is fail!" <<endl;
		return -1;
	}
	//print hello buffer
	string hellostr = buffer;
	cout << "data:" << hellostr << endl;


	int threadNum = 10;
	atomic<int> execedThreadNum = 0;
	
	auto threadfuc = [client,data,&execedThreadNum](int tnum){
		std::string tnumstr = to_string(tnum) + "_";
		//pkg content size
		DATA_SIZE contentsize = tnumstr.size() + strlen(data);
		//pkg header + content size
		DATA_SIZE headersize = strlen(PKG_HEADER) + sizeof(DATA_SIZE);
		//pkg = mtcd+contentsize+content 
		DATA_SIZE pkgSize = headersize + contentsize;
		char* databuf = (char*)calloc(pkgSize,sizeof(char));

		//cpy header
		memcpy(databuf,PKG_HEADER,strlen(PKG_HEADER));
		//cpy contentsize
		memcpy((databuf+strlen(PKG_HEADER)),&contentsize,sizeof(DATA_SIZE));
		//cpy content - tnum
		memcpy((databuf+headersize),tnumstr.c_str(),tnumstr.size());
		//cpy content
		memcpy((databuf+headersize+tnumstr.size()),data,strlen(data));

 		int sendnum = 10000;
		for(int i=0;i<sendnum;i++){
			client->write(databuf,pkgSize);
		}
		execedThreadNum++;
	};

	for(int i=0;i<threadNum;i++){
		thread t(threadfuc,i);
		t.detach();
	}

	//send buffer to server
	while(1){
		if(execedThreadNum == threadNum){
			break;
		}
#ifdef _WIN32
		Sleep(1000);
#else
		usleep(100000);
#endif
	}
	//close client
	client->close();
	delete client;

	cout << "task end" << endl;

#ifdef _WIN32
	system("pause");
#else
	cout << "Press Enter to Continue..." << endl;
	char ccc = getchar();
#endif
	return 0;
}
