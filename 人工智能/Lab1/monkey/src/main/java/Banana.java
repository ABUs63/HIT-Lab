//120L021905 ����
public class Banana {
    private Location location = new Location();//�㽶��λ��
    private boolean hang;//�㽶�Ƿ�����

    public Location getLocation() {
        return location;
    }

    public void setLocation(int x,int y) {
        location.set(x,y);
    }

    public boolean isHang() {
        return hang;
    }

    public void setHang(boolean hang) {
        this.hang = hang;
    }
}
