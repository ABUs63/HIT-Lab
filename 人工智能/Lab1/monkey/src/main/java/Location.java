import java.util.Objects;

//120L021905 ����
public class Location {

    private int x;//x����
    private int y;//y����

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public Location(int x, int y) {//���캯��
        this.x = x;
        this.y = y;
    }

    public Location(){//���캯��

    }

    public void set(int x,int y){//�����޸�λ����
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
