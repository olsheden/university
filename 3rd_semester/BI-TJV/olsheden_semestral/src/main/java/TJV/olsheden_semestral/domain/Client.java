package TJV.olsheden_semestral.domain;

import javax.persistence.*;
import java.util.*;

@Entity
@Table(name = "client")
public class Client{

    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "client_generator")
    @SequenceGenerator (name = "client_generator", sequenceName = "Client_seq", allocationSize = 1)
    private Long id;

    private String name;

    private String surname;

    private Long age;


    @OneToMany(mappedBy = "client", cascade = CascadeType.REMOVE)
    private Set<Order> orders;


    public Client(Long id, String name, String surname, Long age) {
        this.id = id;
        this.name = name;
        this.surname = surname;
        this.age = age;
        orders = new HashSet<>();
    }

    public Client(Long id, String name, String surname, Long age, Set<Order> orders) {
        this.id = id;
        this.name = name;
        this.surname = surname;
        this.age = age;
        this.orders = orders;
    }

    public Client() {

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

    public String getSurname() {
        return surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public Long getAge() {
        return age;
    }

    public void setAge(Long age) {
        this.age = age;
    }

    public Set<Order> getOrders() {
        return orders;
    }

    public void setOrders(Set<Order> orders) {
        this.orders = orders;
    }

    public void addOrder(Order order) {
        if (orders.contains(order)) return;
        orders.add(order);
    }

    public void deleteOrder(Order order){
        if (orders.contains(order)) {
            orders.remove(order);
        }
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Client client = (Client) o;
        return Objects.equals(id, client.id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    @Override
    public String toString() {
        return "Client{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", surname='" + surname + '\'' +
                ", age=" + age +
                ", orders=" + orders +
                '}';
    }
}
