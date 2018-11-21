#include <iostream>
#include <fstream>
#include <list>
#include <set>
#include <vector>
using namespace std;

class Text_editor {
public:

    explicit Text_editor()//初始化editor，使链表里存了这个文章
    {
        cout << "Text editor starts!" << endl;
        total_line=0;
        ops = {'R', 'W', 'I', 'D', 'F', 'C', 'Q', 'H', 'N', 'P', 'B', 'E', 'G', 'V'};
        master();//一直监听用户输入。
    }

    ~Text_editor() {
        cout << "Text editor exited!" << endl;
    }

    void master() {
        char cur_op;
        while (cur_op = read_operation()) {
            if (ops.count(cur_op) == 1)//如果cur_op是操作符，则需要执行操作，如果不是，则继续要求读入
            {
                switch (cur_op) {
                    case 'R': {
                        cout << "Please enter the cur_path" << endl;
                        cout << "cur_path: ";
                        cin >> cur_path;
                        read_file(cur_path);
                    }
                        break;
                    case 'W':
                    {
                        write_file(cur_path);
                    }
                        break;
                    case 'I':
                    {
                        string newline;
                        int index;
                        cout<<"please input the index of new line\n";
                        cin>>index;
                        cout<<"please input the new line\n";
                        cin>>newline;

                        insert_line(index,newline);
                    }
                        break;
                    case 'D':
                    {
                        del_cur_line();
                    }
                        break;
                    case 'F':
                    {
                        cout<<"input 0 if you want to start at current line\n";
                        cout<<"input 1 if you want to start at the beginning of the article\n";
                        int flag;
                        cin>>flag;
                        cout<<"input the substr you want to find"<<endl;
                        string target;
                        cin>>target;

                        find_line_by_substr(flag,target);
                    }
                        break;
                    case 'C':
                    {
                        int flag;
                        string a,b;
                        cout<<"input '0' for replacement in current line,'1' for the whole article\n";
                        cin>>flag;
                        cout<<"input the substring to be replaced"<<endl;
                        cin>>a;
                        cout<<"input the new string to replace the substring"<<endl;
                        cin>>b;
                        change(flag,a,b);
                    }
                        break;
                    case 'Q': {
                        cout << "text edit exited!" << endl;
                        return;
                    }
                    case 'H':
                    {
                        ;
                    }
                        break;

                    case 'N': {
                        loc_line(cur_op);
                    }
                        break;
                    case 'P': {
                        loc_line(cur_op);
                    }
                        break;
                    case 'B': {
                        loc_line(cur_op);
                    }
                        break;
                    case 'E': {
                        loc_line(cur_op);
                    }
                        break;

                    case 'G':
                    {
                        int index;
                        cout<<"please enter index:"<<endl;
                        cin>>index;
                        cur_line_to_given_line(index);
                    }
                        break;
                    case 'V': {

                        view_buffer();
                    }
                        break;
                }
            } else {
                cout << "please input the right operation!" << endl;
            }
        }
    }

private:
    list<string> article;
    set<char> ops;
    pair<int,list<string>::iterator> cur_line;//指向当前行的迭代器
    int total_line;//也可能会等于0的
    bool article_loaded= false;
    string cur_path;
protected:
    void read_file(const string path) {
        total_line = 0;
        ifstream infile(path);
        string line;
        article.clear();
        if (infile.is_open()) {
            while (getline(infile, line)) {
                article.push_back(line);
            }
            total_line = article.size();
            article_loaded = true;
            cur_line = make_pair(1, article.begin());
        } else {
            cout << "fail to open file!" << endl;
            exit(0);
        }
    }
    void write_file(string path)
    {
        ofstream outfile(path);
        if(outfile.is_open())
        {
            for (string &line:article) {
                outfile<<line<<'\n';
            }
            cout<<"success to write file!"<<endl;
        }
        else
        {
            cout << "fail to write file!" << endl;
            exit(0);
        }
    }



    list<string>::iterator find_line_by_index(int index)
    {
        int offset=index-cur_line.first;
        if(offset>0)
        {
            while(index>cur_line.first)
            {
                cur_line.first++;
                cur_line.second++;
            }
        }
        if(offset==0)
        {
            return cur_line.second;
        }
        if(offset<0)
        {
            while (index<cur_line.first)
            {
                cur_line.first--;
                cur_line.second--;
            }
        }
        return cur_line.second;
    }
    void loc_line(char op) {
        if (!article_loaded) {
            cout << "haven't loaded a file" << endl;
            return;
        }
        switch (op) {
            case 'N': {
                if (cur_line.first < article.size()) {
                    cur_line.first++;
                    cur_line.second++;
                    cout<<"current line:\n";
                    cout<<*cur_line.second;
                } else {
                    cout << "already at the end" << endl;
                }
            }
                break;
            case 'P': {
                if (cur_line.second != article.begin()) {
                    cur_line.first--;
                    cur_line.second--;
                    cout<<"current line:\n";
                    cout<<*cur_line.second;
                } else {
                    cout << "already at the beginning" << endl;
                }
            }
                break;
            case 'B': {
                cur_line.first=1;
                cur_line.second = article.begin();
                cout<<"current line:\n";
                cout<<*cur_line.second;
            }
                break;
            case 'E': {
                cur_line.first=total_line;
                cur_line.second= article.end();
                cur_line.second--;
                cout<<"current line:\n";
                cout<<*cur_line.second;
            }
                break;
        }
    }

    void cur_line_to_given_line(int index){
        find_line_by_index(index);
        cout<<"the current line is:\n";
        cout<<*cur_line.second;
    }
    void view_buffer() {
        if (!article_loaded) {
            cout << "haven't loaded a file" << endl;
            return;
        }
        cout << "========Buffer:========" << endl;
        int index=0;
        cout<<"index    content\n";
        for (string &line:article) {
            index++;
            cout << index<<"        "<<line << endl;
        }
    }

    void del_cur_line(){
        if (!article_loaded) {
            cout << "haven't loaded a file" << endl;
            return;
        }
        article.erase(cur_line.second);
        cur_line.first++;
        cur_line.second++;
    }
    void insert_line(int index,string newline){
        if (!article_loaded) {
            cout << "haven't loaded a file" << endl;
            return;
        }
        find_line_by_index(index);
        article.insert(cur_line.second,newline);
    }
    void find_line_by_substr(int flag,string target)
    {
        if(flag==0)//从开始当前行
        {

            for(auto it=cur_line.second;it!=article.end();it++)
            {
                if(is_find(*it,target))
                {
                    cout<<"find at this line:"<<endl;
                    cout<<*it;
                    return;
                }
            }
            cout<<"No found!";
            return;
        }
        if(flag==1)
        {
            for(auto it=article.begin();it!=article.end();it++)
            {
                if(is_find(*it,target))
                {
                    cout<<"find at this line:"<<endl;
                    cout<<*it;
                    return;
                }
            }
            cout<<"No found!";
            return;
        }
    }
    bool is_find(string& origin,string target)
    {
        int i=0;
        while(i<origin.size())
        {
            string cut=origin.substr(i,target.size());
            if(cut==target)
            {
                return true;
            }
            i++;
        }
        return false;
    }
    //对一个字符串进行多次子串替换（使用vector记录替换前待替换子串的下标位置，
    // 加上替换前后的长度差的倍数来处理每次替换之后的下标变化）
    void one_change(string& origin,const string& a,const string& b)//将origin中的a替换为b
    {
        vector<unsigned long long int> pos;
        pos.clear();
        string cut;
        unsigned long long int fix=b.size()-a.size();
        unsigned long long int i=0;
        while(i<origin.size())
        {
            cut=origin.substr(i,a.size());//提取子串，通过比对进行查找
            if(cut==a)
            {
                pos.push_back(i);
            }
            i++;
        }
        int k=0;
        //处理每次替换之后的下标变化
        for(int j=0;j<pos.size();j++)
        {
            origin.replace(pos[j]+fix*k,a.size(),b);
            k++;
        }

    }
    void change(int flag,const string& a,const string& b)//flag=0：在当前行有效；flag=1：在全文有效。a:待替换字符；b：替换成的字符
    {

        if(flag==0)//仅当前行有效
        {
            one_change(*cur_line.second,a,b);

        }
        else
        {
            for(auto i=article.begin();i!=article.end();i++)//遍历所有行
            {
                one_change(*i,a,b);
            }
        }

    }

    char read_operation() {//读入操作符，判断是否是字母。若是，则统一转换为大写字母。
        char op;
        cin >> op;
        if ((op >= 'a' && op <= 'z') || (op >= 'A' && op <= 'Z'))//若输入的是字母
        {
            if ((op >= 'a' && op <= 'z'))//转换为大写的;
            {
                op -= 32;
            }
        }
        return op;
    }

};


int main() {

    Text_editor *editor = new Text_editor();

    return 0;
}