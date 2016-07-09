


bool findsMinotaur(char maze[][10], int er, int ec)
{

    if (maze[er][ec]=='M')
        return true;
    else
    {
        maze[er][ec]='Q';
    }
   
    
    

    if(maze[er-1][ec]!='Q' && maze[er-1][ec]!='X')
    {
        
        if(findsMinotaur(maze, er-1, ec))
            return true;
        
    }



    if(maze[er][ec+1]!='Q' && maze[er][ec+1]!='X')
    {
        if(findsMinotaur(maze, er, ec+1))
            return true;
    }

    if(maze[er+1][ec]!='Q' &&  maze[er+1][ec]!='X')
    {
        if (findsMinotaur(maze, er+1, ec))
            return true;
    }



    if(maze[er][ec-1]!='Q'&& maze[er][ec-1]!='X')
    {
        if (findsMinotaur(maze, er, ec-1))
            return true;
    }


    
    return false;
}