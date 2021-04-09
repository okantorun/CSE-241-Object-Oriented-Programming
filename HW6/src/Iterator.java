

public class Iterator<E>
{

	private Object[] myarray;
	private int index;
	private int size;

	public Iterator(Object[] obj,int indexx,int _size) {
		myarray=obj;
		size=_size;					//values needed to start
		index=indexx;
		
	}
	/**
		*Reaches the next element of the object.
		*@return next element of the object.
	*/
	public  E next() {
		return (E)myarray[index++];				
	}

	/**
		*In the next step, it is checked whether it is an element.
		*@return returns false if there is no element in the next step.
	*/
	public boolean hasnext() {
		
		if((index+1)>size)
			return false;			
		else
			return true;
	}

	public void remove() {
        throw new UnsupportedOperationException();
    }

			
}
	

