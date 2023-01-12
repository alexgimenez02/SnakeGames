import java.util.LinkedList;

public class Food{
	private int positionX;
	private int positionY;
	
	public Food(){
		positionX = positionY = 0;
	}
	
	public void GenerateNewPosition(Snake snake, Board board){
		int max = board.getWidth();
		int min = board.getHeight();
		int[] head = snake.getHeadPosition();
		LinkedList<Integer> bodyX = snake.getBodyX();
		LinkedList<Integer> bodyY = snake.getBodyY();
		
		while(true){
			positionX = (int)Math.floor(Math.random() * (max - min + 1) + min);
			positionY = (int)Math.floor(Math.random() * (max - min + 1) + min);
			if(head[0] == positionX && head[1] == positionY){
				continue;
			}
			for(int i = 0; i < bodyX.size(); i++){
				if(bodyX.get(i) == positionX && bodyY.get(i) == positionY){
					continue;
				}
			}
			break;
		}
	}
	
}