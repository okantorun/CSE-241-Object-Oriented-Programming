
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.Container;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JFrame;
import java.awt.Font;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import java.io.FileWriter;  // Import the File class
import java.io.IOException; 
import java.io.File;
import java.util.Scanner;
import java.io.FileNotFoundException;

public class NewWindow extends JFrame implements ActionListener, HexGame ,Cloneable
{	
	private Cell temp = new Cell();
	private Cell copy_Cells[];
	private int size;
	private int selection;
	private int counter;
	private int used;
	private JButton resetButton;
	private JButton saveButton;
	private JButton loadButton;
	private JButton undoButton;
	private JButton button[][];
	private JPanel gamePAN;
	private String saveName;
	private String loadName;


	public int get_size()
	{
		return size;
	}
	public int get_counter()
	{
		return counter;
	}
	public int get_selection()
	{
		return selection;
	}
	NewWindow(int _size,int _selection)
	{	
		size=_size;
		counter=0;
		used=0;
		if(_selection==0)
			selection=1;
		else{
			selection=_selection;
		}
		copy_Cells = new Cell[size*size];
		initComponents();
		initialize();	
	}
	
	public void initComponents(){
		gamePAN = new JPanel();
		JFrame frame = new JFrame();
		frame.setSize(750,600);			
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);			//frame and panel's initial values
		frame.add(gamePAN);
		gamePAN.setBounds(50,70,670,530);
		frame.setVisible(true);
	}
	public void initialize()
	{
		gamePAN.setLayout(new GridLayout(size, size*2));//It doubles the width of the board to have a parallelogram shape.
		button = new JButton[size][size];					//button array representing cells
		
		JButton[] emptyButton = new JButton[size*10];
		
		int shiftCounter=0;


		for(int i=0;i<size;i++){
			for(int k=0;k<i;k++){
				emptyButton[shiftCounter] = new JButton();		//I'm adding empty buttons to make the board a parallelogram.
				emptyButton[shiftCounter].setContentAreaFilled(false);
				emptyButton[shiftCounter].setBorderPainted(false);
				gamePAN.add(emptyButton[shiftCounter]);
				shiftCounter++;
			}
			for(int j=0;j<size*2-i;j++){
				if(j<size)
				{
					button[i][j] = new JButton(".");
					button[i][j].addActionListener(this);
					button[i][j].setContentAreaFilled(false);
					button[i][j].setBorderPainted(false);
					button[i][j].setSize(20,20);
					gamePAN.add(button[i][j]);
				}
				else
				{
					if(i==0 && j==size*2-i-1){
						resetButton = new JButton();
						gamePAN.add(resetButton);
						resetButton.addActionListener(this);		//reset button
						resetButton.setText("Reset");
						resetButton.setFont(new Font("Arial",Font.PLAIN,10));
						resetButton.setSize(10,10);
					}
					else if(i==1 && j==size*2-i-1){
						saveButton = new JButton();
						gamePAN.add(saveButton);
						saveButton.addActionListener(this);
						saveButton.setText("Save");				//I add the necessary buttons to the right of the panel
						saveButton.setFont(new Font("Arial",Font.PLAIN,10));
						saveButton.setSize(10,10);
					}
					else if(i==2 && j==size*2-i-1){
						undoButton = new JButton();
						gamePAN.add(undoButton);						//undo button
						undoButton.addActionListener(this);
						undoButton.setText("Undo");
						undoButton.setFont(new Font("Arial",Font.PLAIN,10));
						undoButton.setSize(10,10);
					}
					else if(i==3 && j==size*2-i-1){
						loadButton = new JButton();
						gamePAN.add(loadButton);
						loadButton.addActionListener(this);			//load button
						loadButton.setText("Load");
						loadButton.setFont(new Font("Arial",Font.PLAIN,10));
						loadButton.setSize(10,10);
					}
					else{
						emptyButton[shiftCounter] = new JButton();
						emptyButton[shiftCounter].setContentAreaFilled(false);
						emptyButton[shiftCounter].setBorderPainted(false);
						gamePAN.add(emptyButton[shiftCounter]);

					}
				}
			}
		}
		setVisible(true);
	}
	
	public void actionPerformed(ActionEvent e){
		Cell compMove = new Cell();

		if(e.getSource()==resetButton)
			reset();
		else if(e.getSource()==saveButton)
			writeToFile();
		else if(e.getSource()==undoButton)
			undo();
		else if(e.getSource()==loadButton){
			readFromFile();
		}

		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				if(e.getSource()==button[i][j]){
					if(button[i][j].getText().equals("x") || button[i][j].getText().equals("o")){
						JOptionPane.showMessageDialog(null,"This move has been made before.");
						counter--;
					}
					else if(counter%2==0 && selection==2){
						button[i][j].setText("x");
						addElement(i,j);
					}											//playGame
					else if(get_selection()==2){
						button[i][j].setText("o");
						addElement(i,j);
					}
					else if(selection==1){
						button[i][j].setText("x");
						addElement(i,j);
						compMove=play();
						button[compMove.get_compRow()][compMove.get_compCol()].setText("o");
						addElement(compMove.get_compRow(),compMove.get_compCol());

					}
					if(isEnd_x(0)==1){
						upper(0);
						JOptionPane.showMessageDialog(null,"Congratulations, 'X' Won");
					}
					if(isEnd_o(0)==1){
						upper(0);
						JOptionPane.showMessageDialog(null,"Congratulations, 'O' Won");
					}
					counter++;

				}
			}
			
		}
	}
	public void undo()
	{	
		if(used==0)
		{
			JOptionPane.showMessageDialog(null,"No moves left to erase");
		}
		else if(selection==2)
		{
			button[copy_Cells[used-1].get_copy_row()][copy_Cells[used-1].get_copy_col()].setText(".");
			used--;			//and I'm reducing my move counter.
			counter--;
		}
		else if(selection==1)
		{
			button[copy_Cells[used-1].get_copy_row()][copy_Cells[used-1].get_copy_col()].setText(".");
			used--;			//and I'm reducing my move counter.
			counter--;
			button[copy_Cells[used-1].get_copy_row()][copy_Cells[used-1].get_copy_col()].setText(".");
			used--;			//and I'm reducing my move counter.
			counter--;
		}
	}

	public void addElement(int r,int c)
	{	
		copy_Cells[used] = new Cell();
		copy_Cells[used].set_Copy(r,c);		//I save the coordinates in the variable Cell
		used++;
		
	}

	public Object clone() throws
                CloneNotSupportedException 
    {

    	 starting s = (starting)super.clone(); 				
    	 return s;
    }

	public void reset(){

		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				button[i][j].setText(".");
				counter=0;
			}
		}
	}
	public void writeToFile()
	{	
		try{

			saveName = JOptionPane.showInputDialog( "Enter Save Name" );

			 FileWriter myWriter = new FileWriter(saveName);

			 if(selection==1){ myWriter.write("1\n");}
			 else{ myWriter.write("2\n");}

			 if(counter%2==0){ myWriter.write("0\n");}
			 else{ myWriter.write("1\n");}

			 myWriter.write((char)(size+'0'));
			 myWriter.write("\n");

			 for(int i=0;i<size;i++)
				for(int j=0;j<size;j++)
					myWriter.write(button[i][j].getText());

	      	JOptionPane.showMessageDialog(null,"Successfully wrote to the file.");
	     	 myWriter.close();
	     }
     	 catch (IOException e) {
     		 System.out.println("An error occurred.");
      			e.printStackTrace();
    	}
		
	}
	public void readFromFile()
	{
		try
		{
			String temp;

			
			
			loadName = JOptionPane.showInputDialog( "Enter Load Name" );
			 File myObj = new File(loadName);
	     	 Scanner myReader = new Scanner(myObj);
			
	     	selection=Integer.parseInt(myReader.nextLine());
	     	counter=Integer.parseInt(myReader.nextLine());
	     	size=Integer.parseInt(myReader.nextLine());

	     	initialize();
	     	initComponents();
	     	//button = new JButton[size][size];

	     	for(int i=0;i<size;i++){
				for(int j=0;myReader.hasNext();j++){
					temp=myReader.next();
					//button[i][j] = new JButton(temp);
					System.out.println(button[i][j].getText());
				}
			}
			
			myReader.close();
				

		}
		
		catch (FileNotFoundException e) {
      		System.out.println("An error occurred.");
      		e.printStackTrace();
   		 }
	}		
	public Cell play(){
			int row=0,column=0;
			int c=0;
			int i;
			int j;
			int k,m=0;
			int control=0;
			int control2=0;
			int control_o=0;
			
			
			for(i=0;i<size;i++){
				if(button[0][i].getText().equals("o")==true)
					control++;
			}
			
			if(control==0){										//I'm trying to determine the computer's moves as smart as possible.
				for(i=0;i<size;i++){
					for(j=0;j<size;j++){
						if(button[i][j].getText().equals("o")==true){
							row=i;
							column=j;
							c++;
							break;
						}

					}									
					if(c!=0)
						break;
				}
				if(column+2>=size){						//it checks the board and tries to play a sub-index every time he moves, if it's full, it turns to other alternatives.
					temp=new Cell(0,column-2);
					return temp;
				}
				else{
					temp=new Cell(0,column+2);
					return temp;
				}
				
			}
			else{
				for(k=size-1;k>=0;k--){
					for(m=size-1;m>=0;m--){
						if(button[k][m].getText().equals("o")==true){
							control_o++;
							break;
						}
					}
					if(control_o!=0)
						break;
				}
					
				for(j=m-1;j<m+1;j++){
					if(button[k+1][j].getText().equals(".")==true){
						temp=new Cell(k+1,j);						//I send the computer's move to my cell class with constructor and 
						return temp;							//assigned it to my object that I will return.
					}											
				}
				if(control2==0){
					
					if(button[k][m-1].getText().equals(".")==true){
						temp=new Cell(k,m-1);
						return temp;
					}
					else if(button[k][m+1].getText().equals(".")==true){
						temp=new Cell(k,m+1);
						return temp;
					}
					else{
						temp=new Cell(k+2,m);
						return temp;
					}
				}

			}
			return temp;

		}
	public int isEnd_x(int check_count)
		{
			int i;
			int j;
			if(check_count==get_size())
				return 1;

			for(i=0;i<get_size();i++){
				if(button[i][check_count].getText().equals("x")==true){		//the funciton controls to see if 'x' wins  with recursion.
					for(j=i-1;j<i+1;j++){
						if(j!=-1){
							if(button[j][check_count+1].getText().equals("x")==true){
								return isEnd_x(check_count+2);
							}
						}
					}
				}
			}

			if(check_count==get_size())
				return 1;
			else
				return 0;
		}
	public int isEnd_o(int check_count)
		{
			int i;
			int j;
			if(check_count==get_size())
				return 1;
			for(i=0;i<get_size();i++){
				if(button[check_count][i].getText().equals("o")==true){			//the funciton controls to see if 'o' wins  with recursion.
					for(j=i-1;j<i+1;j++){
						if(button[check_count+1][j].getText().equals("o")==true){
							return isEnd_o(check_count+2);
						}

					}
				}
				
			}
			
			if(check_count==get_size())
				return 1;
			else
				return 0;
		}
	public int upper(int check_count)
		{
			int i;
			int j;
			if(check_count==get_size())
				return 1;
			if(counter%2==0){
				for(i=0;i<size;i++){
					if(button[i][check_count].getText().equals("x")==true){
						for(j=i-1;j<i+1;j++){
							if(j!=-1){
								if(button[j][check_count+1].getText().equals("x")==true){
									button[j][check_count+1].setText("X");
									button[i][check_count].setText("X");
								    upper(check_count+2);

								}
							}
						}
					}
					
				}			////I conver to uppercase the letters of the winning team with the same logic as we find the winner with recursion.
			}
			else if(counter%2==1 && check_count!=get_size()){
				for(i=0;i<get_size();i++){
					if(button[check_count][i].getText().equals("o")==true){
						for(j=i-1;j<i+1;j++){
							if(button[check_count+1][j].getText().equals("o")==true){
								button[check_count+1][j].setText("O");
								button[check_count][i].setText("O");
							    upper(check_count+2);

							}
						}
					}
					
				}

			}
			return 0;
	
		}
		
}