#include <string>  
#include <iostream>

using namespace std;


class ITrack
{
	virtual string getData()=0;
};

class H264 :public ITrack
{
public:
	string getData() { return "get h264 data"; }
	void setBitrate(int bitrate) { m_bitrate = bitrate; }

private:
	int m_bitrate;
};


class AAC :public ITrack
{
public:
	string getData() { return "get aac data"; }

};

class XML :public ITrack
{
public:
	string getData() { return "get xml data"; }

};


class RTSPServer
{
public:
	ITrack* createTrack(string trackType);
};

ITrack* RTSPServer::createTrack(string trackType)
{
	if (trackType == "h264")
	{
		H264 *h264 = new H264();
		h264->setBitrate(12);
		cout << h264->getData() << endl;
		return h264;
	}
	else if (trackType == "aac")
	{
		AAC *aac = new AAC();
		cout << aac->getData() << endl;
		return aac;
	}
	else if (trackType == "xml")
	{
		XML *xml = new XML();
		cout << xml->getData() << endl;
		return xml;
	}
	
}

int main(int argc, char* argv[])
{

	RTSPServer rtspServer;

	ITrack *h264_aac = rtspServer.createTrack("h264");
	h264_aac = rtspServer.createTrack("aac");

	//rtspServer.start();

	system("pause");
	return 0;
}
