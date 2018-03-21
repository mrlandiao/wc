void none()//统计空行数
{
	int i,j = 0;
	for (i = 0;; i++)
	{
		if (art[i] == EOF)
			break;
		if (art[i] != '\n'&& art[i] != '\t'&& art[i] != ' ')
		{
			j++;
			//统计单词数、行数、注释行数//统计单词数、行数、注释行数//统计单词数、行数、注释行数//统计单词数、行数、注释行数
			//统计单词数、行数、注释行数
		}
		if (art[i] == '\n')
		{
			if (j <= 1)
				none_num++;
			j = 0;
		}
	}
}
//统计单词数、行数、注释行数
int count()
{
	//统计单词数、行数、注释行数
	get();
	clearToken();
	//统计单词数、行数、注释行数
	while (isSpace(ch) || isNewline(ch) || isTab(ch) || isComma(ch))
	{
		if (isNewline(ch)) line_num++;
		get();
	}
	if (isStar(ch))
	{
		catToken(ch);
		//统计单词数、行数、注释行数
	}
	else if (isDivi(ch))
	{
		catToken(ch);
		get();
		//统计单词数、行数、注释行数
		if (isStar(ch))
		{
			note_num++;
			catToken(ch);
			do
			{
				do
				{
					get();
					if (isNewline(ch))
					{
