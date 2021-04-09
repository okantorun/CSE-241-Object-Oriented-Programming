
import java.awt.FlowLayout;
import javax.swing.JOptionPane;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemListener;
import java.awt.BorderLayout;
import java.awt.event.ItemEvent;
import javax.swing.JLabel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JRadioButton;
import javax.swing.ButtonGroup;
import java.awt.GridLayout;
public class starting extends JFrame 
{
	//protected JButton buttons[];
	protected String string = "1"; 
	protected JLabel label1;
	protected int selection;
	private JPanel buttonJPanel;
	protected JTextField textField; // used to display font changes
	protected JRadioButton radioButton_comp;
	protected JRadioButton radioButton_user;
	protected JRadioButton italicJRadioButton; // selects italic text
	protected JRadioButton boldItalicJRadioButton; // bold and italic
	protected ButtonGroup radioGroup; // buttongroup to hold radio buttons
 	// starting constructor adds JRadioButtons to JFrame
	public starting()
	{
		super( "Starting" );
		setLayout( new FlowLayout() ); // set frame layout
	} // end starting constructor
	public void FirstPanel()
	{
		label1 = new JLabel( "Please Enter Size Of Board" );
		add( label1 ); // add label1 to JFrame
		textField = new JTextField(25);
		add( textField ); // add textField to JFrame			//start screen, board size and user selection
		
		radioButton_comp = new JRadioButton( "Computer vs User", true );
		radioButton_user = new JRadioButton( "User vs User", false );
		
		add( radioButton_comp ); // add plain button to JFrame
		add( radioButton_user ); // add bold button to JFrame
		
		 // create logical relationship between JRadioButtons
		radioGroup = new ButtonGroup(); // create ButtonGroup
		radioGroup.add( radioButton_comp ); // add plain to group
		radioGroup.add( radioButton_user ); // add bold to group

		RadioButtonHandler handler2 = new RadioButtonHandler();
		radioButton_comp.addItemListener(handler2);
		radioButton_user.addItemListener(handler2);

		TextFieldHandler handler = new TextFieldHandler();
		textField.addActionListener( handler );
		setVisible(true);
		setSize( 300, 300 );
	}
	
// private inner class to handle radio button events
	private class RadioButtonHandler implements ItemListener
	{
		
		public void itemStateChanged( ItemEvent event )
		{
			Cell temp = new Cell();
			
			if(event.getSource()==radioButton_comp)		//user selection
			{
				selection=1;
			}
			else if(event.getSource()==radioButton_user)
			{
				selection=2;
			}
			
		} 

	} 

	private class TextFieldHandler implements ActionListener
	{	
		
		public int get_str()
		{
			return  Integer.parseInt(string);
		}
		public void actionPerformed( ActionEvent event )		//board size 

		{
			if ( event.getSource() == textField ){
				string = String.format(event.getActionCommand()); 
			}
			
			setVisible(false);
			NewWindow myWindow = new NewWindow(get_str(),selection);		//I close this screen and send the board size and user selection to the new window
		}

	} 
	
}