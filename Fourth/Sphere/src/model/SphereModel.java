package model;

/**
 *
 * @author wangyuanlong
 */

import java.util.Observable;
public class SphereModel extends Observable {
    private double radius;
    /** Creates a new instance of Sphere */
    public SphereModel(double radius) {
        this.radius=radius;
    }

    public double getRadius() {
        return radius;
    }
    
    public void setRadius(double radius) {
    	if(radius<0){//对传入数据进行过滤
    		this.radius=0;
    	}else{
    		this.radius=radius;
    	}
         this.setChanged();
	     this.notifyObservers();
    }
    

    public double volume() {
        return (double)4/(double)3*Math.PI*radius*radius*radius;
    }

    public double surfaceArea() {
        return 4*Math.PI*radius*radius;
    }
    
}
