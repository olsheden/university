package TJV.olsheden_semestral.dtos;

import TJV.olsheden_semestral.domain.Order;
import com.fasterxml.jackson.annotation.JsonView;

import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import java.util.Collection;
import java.util.List;
import java.util.Set;

public class ClientDto {


    public Long id;


    public String name;


    public String surname;


    public Long age;

    public Set<Long> ordersId;

    public ClientDto() {
    }

    public ClientDto(Long id, String name, String surname, Long age, Set<Long> ordersId) {
        this.id = id;
        this.name = name;
        this.surname = surname;
        this.age = age;
        this.ordersId = ordersId;
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

    public void setOrdersId(Set<Long> ordersId) {
        this.ordersId = ordersId;
    }
}
