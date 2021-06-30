#include <bits/stdc++.h>
using namespace std;
static int f=0;
stack<long double> r;

void Addition()
{
    long double a,b,result;
    b=r.top();
    r.pop();
    a=r.top();
    r.pop();
    result=a+b;
    r.push(result);
}

void Substraction()
{
    long double a,b,result;
    b=r.top();
    r.pop();
    a=r.top();
    r.pop();
    result=a-b;
    r.push(result);
}

void Multiplication()
{
    long double a,b,result;
    b=r.top();
    r.pop();
    a=r.top();
    r.pop();
    result=a*b;
    r.push(result);
}

void Division()
{
    long double a,b,result;
    b=r.top();
    r.pop();
    a=r.top();
    r.pop();
    if(b==0)f=1;
    else
    result=a/b;
    r.push(result);
}

string POSTFIX(string infix)
{
    string postfix,d;
    stack<char> s;
    int p=0,j,i,c=0;
    for(i=0;i<infix.size();i++)
    {
        if(infix[i]==' ')continue;
        if((infix[i]>='0'&&infix[i]<='9')||infix[i]=='.')
        {
            for(j=i; j<infix.size(); j++)
            {
                if(infix[j]=='+'||infix[j]=='-'||infix[j]=='*'||infix[j]=='/'||infix[j]==' '||infix[j]=='('||infix[j]==')')break;
            }
            d=infix.substr(i,j-i);
            postfix+=d;
            postfix+=' ';
            i=j-1;
            c++;
            continue;
        }
        c++;
        switch(infix[i])
        {
        case '+':
            while(p>=1)
            {
                postfix+=s.top();
                postfix+=' ';
                s.pop();
                if(s.empty())
                    p=0;
                else if(s.top()=='+'||s.top()=='-')
                    p=1;
                else if(s.top()=='*'||s.top()=='/')
                    p=2;
                else
                    p=0;
            }
            s.push(infix[i]);
            p=1;
            break;
        case '-':
            while(p>=1)
            {
                postfix+=s.top();
                postfix+=' ';
                s.pop();
                if(s.empty())
                    p=0;
                else if(s.top()=='+'||s.top()=='-')
                    p=1;
                else if(s.top()=='*'||s.top()=='/')
                    p=2;
                else
                    p=0;
            }
            s.push(infix[i]);
            p=1;
            break;
        case '*':
            while(p>=2)
            {
                postfix+=s.top();
                postfix+=' ';
                s.pop();
                if(s.empty())
                    p=0;
                else if(s.top()=='+'||s.top()=='-')
                    p=1;
                else if(s.top()=='*'||s.top()=='/')
                    p=2;
                else
                    p=0;
            }
            s.push(infix[i]);
            p=2;
            break;
        case '/':
            while(p>=2)
            {
                postfix+=s.top();
                postfix+=' ';
                s.pop();
                if(s.empty())
                    p=0;
                else if(s.top()=='+'||s.top()=='-')
                    p=1;
                else if(s.top()=='*'||s.top()=='/')
                    p=2;
                else
                    p=0;
            }
            s.push(infix[i]);
            p=2;
            break;
        case '^':
            while(p>=3)
            {
                postfix+=s.top();
                postfix+=' ';
                s.pop();
                if(s.empty())
                    p=0;
                else if(s.top()=='+'||s.top()=='-')
                    p=1;
                else if(s.top()=='*'||s.top()=='/')
                    p=2;
                else
                    p=0;
            }
            s.push(infix[i]);
            p=3;
            break;
        case '(':
            s.push(infix[i]);
            p=0;
            break;
        case ')':
            while(s.top()!='(')
            {
                postfix+=s.top();
                postfix+=' ';
                s.pop();
            }
            s.pop();
            if(s.empty())
                p=0;
            else if(s.top()=='+'||s.top()=='-')
                p=1;
            else if(s.top()=='*'||s.top()=='/')
                p=2;
            else
                p=0;
            break;
        default:
            break;
        }
    }
    while(!s.empty())
    {
        postfix+=s.top();
        postfix+=' ';
        s.pop();
    }
    if(c%2==0)f=1;
    return postfix;
}




int main()
{
    int i,j,a=0,c=1,cc=1,x;
    long double d;
    string infix,postfix,s;
    cout<<"Input the INFIX Expression: "<<endl;
    getline(cin,infix);


    //input validation check
    x=infix.size();
    for(i=0;i<x;i++)
    {
        if(infix[i]==' ')continue;
        if(infix[i]=='(')a++;
        else if(infix[i]==')')a--;
        else if((infix[i]<'0'||infix[i]>'9')&&infix[i]!='.'&&infix[i]!='+'&&infix[i]!='*'&&infix[i]!='/'&&infix[i]!='-')f=1;
        if(c&&(infix[i]=='+'||infix[i]=='-'||infix[i]=='*'||infix[i]=='/'))c=0,f=1;
        else if(infix[i]!=')'&&infix[i]!='(')c=0;
        if(cc&&(infix[x-1-i]=='+'||infix[x-1-i]=='-'||infix[x-1-i]=='*'||infix[x-1-i]=='/'))cc=0,f=1;
        else if(infix[x-1-i]!=')'&&infix[x-1-i]!='(')cc=0;
    }
    if(f||a)
    {
        cout<<endl<<endl<<"Your INFIX Expression is invalid!!!!!"<<endl;
        exit(1);
    }

    //converting infix expression to postfix expression
    postfix=POSTFIX(infix);


    //evaluating the final result
    for (i=0;i<postfix.size();i++)
    {
        if(postfix[i]==' ')continue;
        if(postfix[i]=='+')Addition();
        else if(postfix[i]=='-')Substraction();
        else if(postfix[i]=='*')Multiplication();
        else if(postfix[i]=='/')Division();
        else
        {
            for(j=i; j<postfix.size(); j++)
            {
                if(postfix[j]=='+'||postfix[j]=='-'||postfix[j]=='*'||postfix[j]=='/'||postfix[j]==' ')break;
            }
            s=postfix.substr(i,j-i);
            d=stod(s);
            r.push(d);
            i=j-1;
        }
    }

    if(f||a)
    {
        cout<<endl<<endl<<"Your INFIX Expression is invalid!!!!!"<<endl;
        exit(1);
    }


    cout<<endl<<endl<<"The POSTFIX Expression is: "<<postfix<<endl;
    cout<<endl<<endl<<"The POSTFIX Evaluation result is: "<<fixed<<setprecision(5)<<r.top()<<endl<<endl;

}

