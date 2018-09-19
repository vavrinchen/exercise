#include <string>  
#include <iostream>

using namespace std;


class ITrack
{
	virtual string getData() { return ""; };
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
	virtual ITrack* createTrack();
};


ITrack* RTSPServer::createTrack()
{
	ITrack *track = new ITrack();
	return track;

}

class H264RTSPServer :public RTSPServer {
public:
	typedef RTSPServer super;
	ITrack* createTrack() {
		H264 *h264 = new H264();
		h264->setBitrate(12);
		cout << h264->getData() << endl;
		return h264;
	}
};

class AACRTSPServer :public RTSPServer {
public:
	typedef RTSPServer super;
	ITrack* createTrack() {
		AAC *aac = new AAC();
		cout << aac->getData() << endl;
		return aac;
	}
};

class XMLRTSPServer :public RTSPServer {
public:
	typedef RTSPServer super;
	ITrack* createTrack() {
		XML *xml = new XML();
		cout << xml->getData() << endl;
		return xml;
	}
};


int main(int argc, char* argv[])
{

	RTSPServer *rtspServer = new H264RTSPServer();
	rtspServer->createTrack();

	rtspServer = new AACRTSPServer();
	rtspServer->createTrack();

	rtspServer = new XMLRTSPServer();
	rtspServer->createTrack();



	system("pause");
	return 0;
}