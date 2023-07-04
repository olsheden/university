package TJV.olsheden_semestral;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.boot.autoconfigure.jdbc.DataSourceAutoConfiguration;
import org.springframework.boot.autoconfigure.security.servlet.SecurityAutoConfiguration;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;

@SpringBootApplication
@Configuration
@ComponentScan({"TJV.olsheden_semestral.converter", "TJV.olsheden_semestral.service", "TJV.olsheden_semestral.controller"})
@EntityScan(basePackages = "TJV.olsheden_semestral.domain")
@EnableJpaRepositories(basePackages = "TJV.olsheden_semestral.repository")
public class OlshedenSemestralApplication {

	public static void main(String[] args) {
		SpringApplication.run(OlshedenSemestralApplication.class, args);
	}

}
