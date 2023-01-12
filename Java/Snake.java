// import java.util.LinkedList;

// public class Snake{
	
	// private int headPositionX;
	// private int headPositionY;
	// private LinkedList<Integer> bodyPositionX;
	// private LinkedList<Integer> bodyPositionY;
	// private Direction direction;
	// private boolean dead;
	
	// public Snake(int x, int y){
		// headPositionX = x;
		// headPositionY = y;
		// bodyPositionX = new LinkedList<>();
		// bodyPositionY = new LinkedList<>();
		// direction = Direction.UP;
	// }
	
	// public int[] getHeadPosition(){
		// int[] position = new int[2];
		// position[0] = headPositionX;
		// position[1] = headPositionY;
		
		// return position;
	// }
	
	// public LinkedList<Integer> getBodyX(){
		// return bodyPositionX;
	// }
	// public LinkedList<Integer> getBodyY(){
		// return bodyPositionY;
	// }
	
	// public void setHeadPosition(int[] position){
		// headPositionX = position[0];
		// headPositionY = position[1];
	// }
	
	// public void addBodyToSnake(){
		// int[] lastBodyPos = new int[2];
		// if(bodyPositionX.size() < 1){
			// lastBodyPos[0] = headPositionX;
			// lastBodyPos[1] = headPositionY;
		// }else{
			// for(int i = 0; i < bodyPositionX.size(); i++){
				// lastBodyPos[0] = bodyPositionX.get(i);
				// lastBodyPos[1] = bodyPositionY.get(i);
			// }
		// }
		// switch(direction){
			// case UP:
				// lastBodyPos[0]--;
				// break;
			// case DOWN:
				// lastBodyPos[0]++;
				// break;
			// case LEFT:
				// lastBodyPos[1]++;
				// break;
			// case RIGHT:	
				// lastBodyPos[1]--;
				// break;
		// }
		// bodyPositionX.add(lastBodyPos[0]);
		// bodyPositionY.add(lastBodyPos[1]);
	// }
	
	// public void updateSnakePosition(){
		// int previousPosX = headPositionX;
		// int previousPosY = headPositionY;
		
		// switch(direction){
			// case UP:
				// headPositionX++;
				// break;
			// case DOWN:
				// headPositionX--;
				// break;
			// case LEFT:
				// headPositionY--;
				// break;
			// case RIGHT:	
				// headPositionY++;
				// break;
		// }
			
		// for(int i = 0; i < bodyPositionX.size(); i++){
			// int tmp_posX = bodyPositionX.get(i);
			// int tmp_posY = bodyPositionY.get(i);
			// if(headPositionX == tmp_posX && headPositionY == tmp_posY){
				// dead = true;
				// break;
			// }else{
				// bodyPositionX.set(i, previousPosX);
				// bodyPositionY.set(i, previousPosY);
				// previousPosX = tmp_posX;
				// previousPosY = tmp_posY;
			// }
		// }
	// }
	
	// public void updateSnakeDirection(Direction dir){
		// direction = dir;
	// }
	
	// public boolean isDead(){
		// return dead;
	// }
// }


import java.awt.EventQueue;
import javax.swing.JFrame;

public class Snake extends JFrame {

    public Snake() {
        
        initUI();
    }
    
    private void initUI() {
        
        add(new Board());
        
        setResizable(false);
        pack();
        
        setTitle("Snake");
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    
    public static void main(String[] args) {
        
        EventQueue.invokeLater(() -> {
            JFrame ex = new Snake();
            ex.setVisible(true);
        });
    }
}