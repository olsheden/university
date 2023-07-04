package TJV.olsheden_semestral.front.domain;

import java.util.Collection;

public class RestaurantDto {

    public Long id;


    public String name;


    public String address;

    public Collection<Long> orderId;

    public RestaurantDto() {
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public Collection<Long> getOrderId() {
        return orderId;
    }

    public void setOrderId(Collection<Long> orderId) {
        this.orderId = orderId;
    }


}
