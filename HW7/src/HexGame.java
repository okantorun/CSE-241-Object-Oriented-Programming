

public interface HexGame
{
	public int isEnd_x(int check_count);
	public int isEnd_o(int check_count);
	public int upper(int check_count);
	public void reset();
	public void writeToFile();
	public void undo();
	public void addElement(int r,int c);
	public void readFromFile();
}