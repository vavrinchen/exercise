//ProxyCustomizeRTSP 當 CustomizeRTSP 的代理人, 讓原本的 videoData 可以根據 VideoType 切換 h264/mjpeg

#include <string>  
#include <iostream>

class InterafaceRTSP
{
public:
	virtual void audioData() = 0;
	virtual void videoData() = 0;
	virtual void metaData() = 0;

};



class CustomizeRTSP :public InterafaceRTSP
{
public:
	CustomizeRTSP() { std::cout << "CustomizeRTSP initial" << std::endl; };
	~CustomizeRTSP() { std::cout << "CustomizeRTSP deconstruct" << std::endl; };
	void audioData() { std::cout << "CustomizeRTSP audioData" << std::endl; };
	void videoData() { std::cout << "CustomizeRTSP videoData" << std::endl; };
	void metaData() { std::cout << "CustomizeRTSP metaData" << std::endl; };

};

class VideoType {
public:
	explicit VideoType(std::string type) : m_type(type) {
	}
	std::string get_type() { return m_type; }
	void set_type(std::string type) { m_type = type; }

private:
	std::string m_type;
};

class ProxyCustomizeRTSP : public InterafaceRTSP 
{ 
public:
	explicit ProxyCustomizeRTSP(VideoType *type) :m_type(type)
	{
		rtsp = new CustomizeRTSP();
	}
	void videoData()
	{
		rtsp->videoData();
		std::cout << m_type->get_type() << std::endl;;
	}
	void audioData()
	{
		std::cout << "ProxyCustomizeRTSP audioData" << std::endl;
	}
	void metaData()
	{
		std::cout << "ProxyCustomizeRTSP metaData" << std::endl;
	}
	void xmlData()
	{
		std::cout << "ProxyCustomizeRTSP xmlData" << std::endl;
	}

private:
	InterafaceRTSP *rtsp;
	VideoType *m_type;
};



int main(int argc, char* argv[])
{

	InterafaceRTSP *rtsp = new ProxyCustomizeRTSP(new VideoType("h264"));
	rtsp->videoData();

	rtsp = new ProxyCustomizeRTSP(new VideoType("mjpeg"));
	rtsp->videoData();

	system("pause");
	return 0;
}
