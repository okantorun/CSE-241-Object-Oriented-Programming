public class Driver
{
	// main method begins program execution

	/**
		*Adding data, deleting data and suppressing its contents are performed on the specified iterator.
		*@param a is collection.
		*@param name is collection name.
	*/
	public static void testCollection(Collection<Integer> a,String name){

		try{
				System.out.printf("**** "+name+" Integer Test ******\n");
				a.add(5);
				a.add(10);
				a.add(7);
				a.add(3);
				a.add(2);
				a.add(17);							
				a.remove(3);
				System.out.print("Removing 3...\n");
				printCollection(a);
				

				System.out.printf("Contains :");
				System.out.println(a.contains(10));
				System.out.printf("Empty :");
				System.out.println(a.isEmpty());
				System.out.printf("Size :");
				System.out.println(a.size());
				
		}	
		catch(Exception e){
				System.out.println(e.getMessage());
		}

	}

	/**
		*A special function for testing queue.
		*@param q is LinkedList collection.
		*@param name is collection name.
	*/
	public static void test_q(LinkedList<Integer> q,String name){

		try{
				System.out.printf("\n\n**** "+name+" Integer Test ******\n");
				q.add(5);
				q.add(10);
				q.add(7);
				q.add(3);
				q.add(2);									
				q.add(17);
				q.remove(10);
				System.out.print("Removing 10...\n");

				System.out.printf("FIFO :");
				System.out.println(q.poll());						
				System.out.printf("Element :");
				System.out.println(q.element());
				System.out.printf("offer :");
				System.out.println(q.offer(95));

				printCollection(q);
				

				System.out.printf("\nContains :");
				System.out.println(q.contains(10));
				System.out.printf("Empty :");
				System.out.println(q.isEmpty());
				System.out.printf("Size :");
				System.out.println(q.size());
				
		}	
		catch(Exception e){
				System.out.println(e.getMessage());
		}

	}
	/**
		*Containsall and retainsall operations are performed for the two collections specified.
		*@param a is LinkedList collection.
		*@param name1 is collection name.
		*@param c is LinkedList collection.
		*@param name2 is collection name.
	*/
	public static void doubleTestCollection(Collection<Integer> a,String name1,Collection<Integer> c,String name2){

		try{
				System.out.printf("\n\n**** "+name1+" and "+name2+" Integer Test ******\n");
				a.add(51);
				a.add(10);
				a.add(70);
				a.add(30);
				a.add(43);
				a.add(48);
				a.add(99);
				a.remove(43);
				System.out.print("Removing 43...\n");

				c.add(1);
				c.add(2);
				c.add(30);
				c.add(51);
				c.add(5);
				c.add(50);
				c.remove(1);
				System.out.print("Removing 1...\n");

				System.out.print(name1+" :");			
				printCollection(a);
				System.out.print(name2+" :");
				printCollection(c);

				System.out.printf("\n****	containsAll  Testing ******\n");
			
				System.out.printf("Contains All :");
				System.out.println(a.containsAll(c));
				
				System.out.printf("\n****	retainAll  Testing ******\n");
			
				a.retainAll(c);
				printCollection(a);

				
				
		}	
		catch(Exception e){
				System.out.println(e.getMessage());
		}
		
	}
	/**
		*Removeall is done for the two collections specified.
		*@param a is LinkedList collection.
		*@param name1 is collection name.
		*@param c is LinkedList collection.
		*@param name2 is collection name.
	*/
	public static void removeAllTestCollection(Collection<Integer> a,String name1,Collection<Integer> c,String name2){

		try{
				System.out.printf("\n\n**** "+name1+" and "+name2+" Integer Test ******\n");
				a.add(51);
				a.add(10);
				a.add(70);
				a.add(30);
				a.add(43);
				a.add(48);
				a.add(99);
				a.remove(99);
				System.out.print("Removing 99...\n");

				c.add(1);
				c.add(2);
				c.add(30);
				c.add(51);
				c.add(5);
				c.add(50);
				c.remove(1);
				System.out.print("Removing 1...\n");

				System.out.print(name1+" :");
				printCollection(a);									
				System.out.print(name2+" :");
				printCollection(c);

				
				System.out.printf("\n****	removeAll  Testing ******\n");
			
				a.removeAll(c);												
				printCollection(a);
				
				
		}	
		catch(Exception e){
				System.out.println(e.getMessage());
		}
		
	}
	/**
		*addall is done for the two collections.
		*@param a is LinkedList collection.
		*@param name1 is collection name.
		*@param c is LinkedList collection.
		*@param name2 is collection name.
	*/
	public static void addAllTestCollection(Collection<Integer> a,String name1,Collection<Integer> c,String name2){

		try{
				System.out.printf("\n\n**** "+name1+" and "+name2+" Integer Test ******\n");
				a.add(51);
				a.add(10);
				a.add(70);
				a.add(30);
				a.add(43);
				a.add(48);
				a.add(99);
				

				c.add(1);
				c.add(2);
				c.add(30);
				c.add(51);
				c.add(5);
				c.add(50);
				

				System.out.print(name1+" :");
				printCollection(a);
				System.out.print(name2+" :");
				printCollection(c);

				
				System.out.printf("\n****	addAll  Testing ******\n");
			
				a.addAll(c);					
				printCollection(a);
				
				
		}	
		catch(Exception e){
				System.out.println(e.getMessage());
		}
		
	}

	/**
		*Iterator operations are performed.
		*@param collection is collection.
	*/
	public static void printCollection(Collection<Integer>collection) {

		Iterator<Integer> iter = collection.iterator();
		while (iter.hasnext()) {
			System.out.print(iter.next() + " ");			
		}
		System.out.println();
	}	

	public static void main( String args[] )throws Exception {
		{
			try{
				LinkedList<Integer> a = new LinkedList<Integer>();
				LinkedList<Integer> b = new LinkedList<Integer>();
				LinkedList<Integer> c = new LinkedList<Integer>();
				LinkedList<Integer> q = new LinkedList<Integer>();			

				HashSet<Integer> d = new HashSet<Integer>();
				HashSet<Integer> e = new HashSet<Integer>();

				ArrayList<Integer> f = new ArrayList<Integer>();
				ArrayList<Integer> h = new ArrayList<Integer>();

				testCollection(a,"LinkedList");
				doubleTestCollection(b,"LinkedList",d,"HashSet");
				removeAllTestCollection(c,"LinkedList",f,"ArrayList");
				addAllTestCollection(e,"HashSet",h,"ArrayList");
				test_q(q,"LinkedList for queue ");
				
			}
			catch(Exception e) {
				System.out.println(e.getMessage());
			}

	}

}
}