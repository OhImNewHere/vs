#include<iostream>
#include <string>
#include <vector>
using namespace std;

struct rec
{
	string s;
	int num;
};

vector<string> split(const  std::string& s, const std::string& delim)
{
	std::vector<std::string> elems;
	size_t pos = 0;
	size_t len = s.length();
	size_t delim_len = delim.length();
	if (delim_len == 0) return elems;
	while (pos < len)
	{
		int find_pos = s.find(delim, pos);
		if (find_pos < 0)
		{
			elems.push_back(s.substr(pos, len - pos));
			break;
		}
		elems.push_back(s.substr(pos, find_pos - pos));
		pos = find_pos + delim_len;
	}
	return elems;
}

void minsert(vector<rec>& pars, string par)
{
	int loc = 0;
	for (int i = 0; i < pars.size(); i++)
	{
		if (par == pars.at(i).s)
		{
			pars.at(i).num++;
			return;
		}
		else if (par < pars.at(i).s)
		{
			break;
		}
		else
		{
			loc++;
		}
	}
	rec nr;
	nr.num = 1;
	nr.s = par;
	pars.insert(pars.begin() + loc, nr);

}

void printres(vector<string> sset)
{
	vector<rec> pars;
	for (int i = 0; i < sset.size(); i++)
	{
		vector<string> subs = split(sset.at(i), " ");
		while (subs.size() != 0 && subs.at(0).length() == 0)
		{
			subs.erase(subs.begin());
		}
		if (subs.size() == 0)	continue;
		for (int j = 1; j < subs.size(); j++)
		{
			if (subs.at(j).length() == 0)
			{
				subs.erase(subs.begin() + j);
				j--;
				continue;
			}
			string temps = subs.at(j - 1) + " " + subs.at(j);
			minsert(pars, temps);
		}
	}
	int maxn = pars.at(0).num;
	int j = 0;
	for (int i = 0; i < pars.size(); i++)
	{
		if (maxn < pars.at(i).num)
		{
			j = i;
			maxn = pars.at(i).num;
		}
	}
	cout << pars.at(j).s << ":" << pars.at(j).num << endl;;

}

int main()
{
	string s;
	vector<string> sset;
	while (getline(cin, s))
	{
		if (s == "####")
		{
			printres(sset);
			sset.clear();
			continue;
		}
		vector<string> a = split(s, ",");
		if (a.size() != 0)
			sset.insert(sset.begin(), a.begin(), a.end());
	}
}