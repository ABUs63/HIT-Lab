//120L021905 郎朗
public class Monkey {
    private Location location = new Location();//猴子当前位置
    private boolean on;//猴子是否在箱子上
    private boolean hold;//猴子是否手中拿到香蕉
    private boolean needbox;//猴子是否需要箱子

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
