#include <string>  
#include <iostream>
#include <vector>

using namespace std;


class ITrack
{
public:
	virtual string getData() = 0;
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
	RTSPServer(ITrack* track);
	void createTrack(ITrack* track);
	void showTrack();

private:
	vector<ITrack *> p_track;
};

RTSPServer::RTSPServer(ITrack* track)
{
	p_track.push_back(track);
}

void RTSPServer::createTrack(ITrack* track)
{
	p_track.push_back(track);
}


void RTSPServer::showTrack()
{
	vector<ITrack *>::iterator iter = p_track.begin();
	for (; iter != p_track.end(); ++iter)
	{
		ITrack *p_track = *iter;
		cout << p_track->getData() << endl;
	}
}

int main(int argc, char* argv[])
{
	RTSPServer *rtspServer = new RTSPServer(new AAC());
	rtspServer->createTrack(new H264());
	rtspServer->createTrack(new H264());
	rtspServer->createTrack(new XML());
	rtspServer->showTrack();

	system("pause");
	return 0;
}