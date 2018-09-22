#include <string>  
#include <iostream>
#include <vector>

using namespace std;


class ITrack
{
public:
	virtual string getData() { return ""; };
};

class H264 :public ITrack
{
public:
	string getData() { return "get h264 data"; }
	void setBitrate(int bitrate) {
		m_bitrate = bitrate;
		cout << "set bitrate: " << m_bitrate << endl;
	}

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
	~RTSPServer();
	virtual ITrack* createTrack(ITrack* track);
	virtual void showTrack();

private:
	vector<shared_ptr<ITrack*>> m_spTrackList;
};

RTSPServer::RTSPServer(ITrack* track)
{

	m_spTrackList.push_back(make_shared<ITrack*>(track));
}

RTSPServer::~RTSPServer()
{

}

ITrack* RTSPServer::createTrack(ITrack* track)
{
	m_spTrackList.push_back(make_shared<ITrack*>(track));
	return track;
}


void RTSPServer::showTrack()
{

	for (const auto& track : m_spTrackList)
	{
		const auto& s = *track;
		cout << s->getData() << endl;
	}
}

int main(int argc, char* argv[])
{
	ITrack* track;
	RTSPServer *rtspServer = new RTSPServer(new AAC());
	track = rtspServer->createTrack(new H264());
	dynamic_cast<H264*>(track)->setBitrate(12);
	rtspServer->createTrack(new H264());
	rtspServer->createTrack(new XML());
	rtspServer->showTrack();

	system("pause");
	return 0;
}