package TJV.olsheden_semestral.front.domain;

import java.util.Collection;

public class ClientDto {


    public Long id;


    public String name;


    public String surname;


    public Long age;

    public Collection<Long> ordersId;

    public ClientDto() {
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

    public Collection<Long> getOrdersId() {
        return ordersId;
    }

    public void setOrdersId(Collection<Long> ordersId) {
        this.ordersId = ordersId;
    }
}

