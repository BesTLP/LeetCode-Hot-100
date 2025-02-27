#include "string"
#include "vector"
#include "iostream"
class BrowserHistory
{
public:
	BrowserHistory(std::string homepage);
	void visit(std::string url);
	std::string back(int steps);
	std::string forward(int steps);


	std::vector<std::string> m_UrlVector;
	std::vector<std::string>::iterator m_NowUrlPointer;

};

BrowserHistory::BrowserHistory(std::string homepage)
{
	m_NowUrlPointer = m_UrlVector.begin();
	visit(homepage);
}

void BrowserHistory::visit(std::string url)
{
	m_NowUrlPointer = m_UrlVector.emplace(m_NowUrlPointer, url);
	m_NowUrlPointer = m_UrlVector.erase(m_UrlVector.begin(), m_NowUrlPointer);
}

std::string BrowserHistory::back(int steps)
{
	while (steps > 0 && m_NowUrlPointer != m_UrlVector.end() - 1)
	{
		steps--;
		m_NowUrlPointer++;
	}
	return m_NowUrlPointer->c_str();
}

std::string BrowserHistory::forward(int steps)
{
	while (steps > 0 && m_NowUrlPointer != m_UrlVector.begin())
	{
		steps--;
		m_NowUrlPointer--;
	}

	return m_NowUrlPointer->c_str();
}
