public class Cell
		{
			
		public Cell()
		{
			comp_Row=1;
			comp_Col=1;
		}
		public Cell(int r,int c)
		{
			comp_Row=r;
			comp_Col=c;
		}	

		public Cell(int r,int c,int user)
		{
			user_row=r;
			user_col=c;
			user_move=user;
		}
		
		public void set_Copy(int copy_row,int copy_col)
		{
			copy_cr_r=copy_row;
			copy_cr_c=copy_col;
		}
		public int get_copy_row(){return copy_cr_r;} 
		public int get_copy_col(){return copy_cr_c;} 
		public int get_compRow() {return comp_Row;}		
		public int get_compCol() {return comp_Col;}
		public int get_userRow() {return user_row;}		
		public int get_userCol() {return user_col;}

		public int selection;
		private int copy_cr_r;
		private int copy_cr_c;
		private int comp_Row;
		private int comp_Col;
		private int user_row;
		private int user_col;
		private int user_move;


}
