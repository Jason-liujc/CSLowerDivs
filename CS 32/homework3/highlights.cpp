
class Highlight
{
    
public:
    Highlight(string name)
    {
        m_name=name;
    }
    
    virtual ~Highlight(){};
     virtual string type() const=0;
    
    void star() const
    {
             cout << m_name;
    }
    
    virtual void commentary() const=0;
    
    
private:
    string m_name;
    
};




class PassingPlay: public Highlight
{
public:
    PassingPlay(string name, int yard)
    :Highlight(name)
    {
        m_yard=yard;
        m_type="Passing Play";
    }
    virtual ~PassingPlay(){};
    
    virtual string type() const
    {
        return m_type;
        
    }
    
    
    virtual void commentary() const
    {
        cout << "complete for " << m_yard << " yards!";
        
        
    }
    
    
private:
    int m_yard;
    string m_type;
    
};


class Interception : public Highlight
{
public:
    Interception(string name, bool Schrodinger_cat)
    :Highlight(name)
    {
        
        m_cat=Schrodinger_cat;
        
        m_type="Interception";
    }
    virtual ~Interception(){};
    
    virtual string type() const
    {
        return m_type;
        
    }
    
    virtual void commentary() const
    {
        if (m_cat==false)
            cout << "That will change the game!";
        else
            cout << "Good for a score!";
        
    }
    
    
private:
    bool m_cat;
    string m_type;
    
};

class RunningPlay:public Highlight
{
public:
    RunningPlay(string name)
    :Highlight(name)
    {
        
        m_type="Running Play";
    }
     virtual ~RunningPlay(){};
    
    virtual string type() const
    {
        return m_type;
        
    }
    
    virtual void commentary() const
    {
        cout << "that will keep the defense honest!";
        
    }
private:
    string m_type;
    
};

