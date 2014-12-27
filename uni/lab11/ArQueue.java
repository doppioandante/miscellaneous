/**
 * ArQueue
 * FIFO Queue, internally implemented using an array
 * @author Enrico Lumetti
 * @see Queue
 * @see EmptyQueueException
 */
public class ArQueue implements Queue
{
    public ArQueue()
    {
	mLength = 0;
	mArray = new Object[INIT_CAPACITY];
	mStartPos = 0;
    }

    @Override
    public Object front() throws EmptyQueueException
    {
	if (isEmpty())
	{
	    throw new EmptyQueueException();
	}

	return mArray[mStartPos];
    }

    @Override
    public Object dequeue() throws EmptyQueueException
    {
	Object result = front();
	mArray[mStartPos] = null;
	mStartPos++;

	return result;
    }

    @Override
    public void enqueue(Object obj)
    {
	if (isFull())
	{
	    if (isEmpty())
	    {
		// just move the cursor to the front
		assert(INIT_CAPACITY != 0);
		mStartPos = 0;
		mLength = 0;
	    }
	    else
	    {
		resize();
	    }
	}

	mArray[mStartPos + mLength] = obj;
	mLength++;
    }

    @Override
    public boolean isEmpty()
    {
	return mStartPos == mLength;
    }


    @Override
    public int size()
    {
	return mLength;
    }

    private boolean isFull()
    {
	return mStartPos + mLength == mArray.length;
    }

    private void resize()
    {
	resize(mArray.length * RESIZE_FACTOR);
    }

    private void resize(int newCapacity)
    {
	assert(newCapacity > mArray.length);

	Object[] newArray = new Object[newCapacity];
	for (int i = 0; i < mLength; i++)
	{
	    newArray[i] = mArray[mStartPos + i];
	}

	mArray = newArray;
    }

    private Object[] mArray;
    private int mLength;
    private int mStartPos;

    private static int INIT_CAPACITY = 0xFF;
    private static int RESIZE_FACTOR = 2;
}
