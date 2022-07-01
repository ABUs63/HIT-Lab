import java.util.Objects;

//120L021905 郎朗
public class Location {

    private int x;//x坐标
    private int y;//y坐标

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public Location(int x, int y) {//构造函数
        this.x = x;
        this.y = y;
    }

    public Location(){//构造函数

    }

    public void set(int x,int y){//后续修改位置用
        this.x = x;
        this.y = y;
    }
    @Override
    public String toString(){
        return "("+x+","+y+")";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Location location = (Location) o;
        return x == location.x && y == location.y;
    }
}
