//120L021905 ����
public class Monkey {
    private Location location = new Location();//���ӵ�ǰλ��
    private boolean on;//�����Ƿ���������
    private boolean hold;//�����Ƿ������õ��㽶
    private boolean needbox;//�����Ƿ���Ҫ����

    public boolean isNeedbox() {
        return needbox;
    }

    public void setNeedbox(boolean needbox) {
        this.needbox = needbox;
    }

    public Location getLocation() {
        return location;
    }

    public void setLocation(int x, int y) {
        location.set(x, y);
    }

    public boolean isOn() {
        return on;
    }

    public void setOn(boolean on) {
        this.on = on;
    }

    public boolean isHold() {
        return hold;
    }

    public void setHold(boolean hold) {
        this.hold = hold;
    }
}
