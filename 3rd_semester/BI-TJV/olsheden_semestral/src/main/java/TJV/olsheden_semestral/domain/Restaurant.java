package TJV.olsheden_semestral.domain;

import javax.persistence.*;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

@Entity
@Table(name = "restaurant")
public class Restaurant {

    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "restaurant_generator")
    @SequenceGenerator (name = "restaurant_generator", sequenceName = "Restaurant_seq", allocationSize = 1)
    private Long id;

    private String name;

    private String address;

    @ManyToMany(mappedBy = "restaurants")
    private Set<Order> orderItems;


    public Restaurant(Long id, String name, String address) {
        this.id = id;
        this.name = name;
        this.address = address;
        orderItems = new HashSet<>();
    }

    public Restaurant(Long id, String name, String address, Set<Order> orders) {
        this.id = id;
        this.name = name;
        this.address = address;
        this.orderItems = orders;
    }

    public Restaurant() {

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

    public Set<Order> getOrderItems() {
        return orderItems;
    }

    public void setOrderItems(Set<Order> orderItems) {
        this.orderItems = orderItems;
    }

    public void addOrder(Order order){
        if(orderItems.contains(order)) return;
        orderItems.add(order);
    }

    public void deleteOrder(Order order){
        if(orderItems.contains(order)){
            orderItems.remove(order);
        }
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Restaurant that = (Restaurant) o;
        return Objects.equals(id, that.id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    @Override
    public String toString() {
        return "Restaurant{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", address='" + address + '\'' +
                ", orderItems=" + orderItems +
                '}';
    }


}
